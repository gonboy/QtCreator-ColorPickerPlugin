#include "colorwatcher.h"

// std includes
#include <set>

// Qt includes
#include <QDebug> //REMOVEME
#include <QRegularExpression>
#include <QTextBlock>
#include <QTextCursor>

// QtCreator includes
#include <coreplugin/editormanager/editormanager.h>

#include <texteditor/texteditor.h>

// Own includes
#include "colorpickerconstants.h"

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorWatcherImpl //////////////////////////

class ColorWatcherImpl
{
public:
    ColorWatcherImpl() :
        colorRegexes()
    {
        // Register regexes
        colorRegexes.insert(ColorType::QCssRgbType, Constants::REGEX_QCSS_RGB_01);
        colorRegexes.insert(ColorType::QCssRgbPercentType, Constants::REGEX_QCSS_RGB_02);
        colorRegexes.insert(ColorType::QCssRgbaAlphaPercentType, Constants::REGEX_QCSS_RGBA_01);
        colorRegexes.insert(ColorType::QCssRgbaAlphaFloatType, Constants::REGEX_QCSS_RGBA_02);
        colorRegexes.insert(ColorType::QssHsvType, Constants::REGEX_QSS_HSV);
        colorRegexes.insert(ColorType::QssHsvaType, Constants::REGEX_QSS_HSVA);
        colorRegexes.insert(ColorType::CssHslType, Constants::REGEX_CSS_HSL);
        colorRegexes.insert(ColorType::CssHslaType, Constants::REGEX_CSS_HSLA);
        colorRegexes.insert(ColorType::QmlRgbaType, Constants::REGEX_QML_RGBA);
        colorRegexes.insert(ColorType::QmlHslaType, Constants::REGEX_QML_HSLA);
        colorRegexes.insert(ColorType::Vec3Type, Constants::REGEX_VEC3);
        colorRegexes.insert(ColorType::Vec4Type, Constants::REGEX_VEC4);
        colorRegexes.insert(ColorType::HexType, Constants::REGEX_HEXCOLOR);
    }

    ~ColorWatcherImpl() {}

    /* functions */
    QColor parseColor(ColorType type, const QRegularExpressionMatch &match) const
    {
        QColor ret;

        if (type == ColorType::QCssRgbType) {
            int r = match.captured(1).toInt();
            int g = match.captured(2).toInt();
            int b = match.captured(3).toInt();

            ret.setRgb(r, g, b);
        }
        if (type == ColorType::QCssRgbPercentType) {
            int r = match.captured(1).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;
            int g = match.captured(2).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;
            int b = match.captured(3).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;

            ret.setRgb(r, g, b);
        }
        else if (type == ColorType::QCssRgbaAlphaPercentType) {
            ret.setRed(match.captured(1).toInt());
            ret.setGreen(match.captured(2).toInt());
            ret.setBlue(match.captured(3).toInt());
            ret.setAlphaF(match.captured(4).remove(QChar::fromLatin1('%')).toFloat() / 100);
        }
        else if (type == ColorType::QCssRgbaAlphaFloatType) {
            ret.setRed(match.captured(1).toInt());
            ret.setGreen(match.captured(2).toInt());
            ret.setBlue(match.captured(3).toInt());
            ret.setAlphaF(match.captured(4).toFloat());
        }
        else if (type == ColorType::QssHsvType) {
            int h = match.captured(1).toInt();
            int s = match.captured(2).toInt();
            int v = match.captured(3).toInt();

            ret.setHsv(h, s,v);
        }
        else if (type == ColorType::QssHsvaType) {
            int h = match.captured(1).toInt();
            int s = match.captured(2).toInt();
            int v = match.captured(3).toInt();

            QString alphaString = match.captured(4).remove(QChar::fromLatin1('%'));
            float a = alphaString.toInt() / 100;

            ret.setHsv(h, s, v);
            ret.setAlphaF(a);
        }
        else if (type == ColorType::CssHslType) {
            int h = match.captured(1).toInt();
            float s = match.captured(2).remove(QChar::fromLatin1('%')).toFloat() / 100;
            float l = match.captured(3).remove(QChar::fromLatin1('%')).toFloat() / 100;

            ret.setHsl(h, s * 255, l * 255);
        }
        else if (type == ColorType::CssHslaType) {
            int h = match.captured(1).toInt();
            float s = match.captured(2).remove(QChar::fromLatin1('%')).toFloat() / 100;
            float l = match.captured(3).remove(QChar::fromLatin1('%')).toFloat() / 100;
            float a = match.captured(4).toFloat();

            ret.setHsl(h, s * 255, l * 255, a);
        }
        else if (type == ColorType::QmlRgbaType) {
            qreal r = match.captured(1).toDouble();
            qreal g = match.captured(2).toDouble();
            qreal b = match.captured(3).toDouble();
            qreal a = match.captured(4).toDouble();

            ret.setRgbF(r, g, b, a);
        }
        else if (type == ColorType::QmlHslaType) {
            qreal h = match.captured(1).toDouble();
            qreal s = match.captured(2).toDouble();
            qreal l = match.captured(3).toDouble();
            qreal a = match.captured(4).toDouble();

            ret.setHslF(h, s, l, a);
        }
        else if (type == ColorType::Vec3Type) {
            float r = match.captured(1).toFloat();
            float g = match.captured(2).toFloat();
            float b = match.captured(3).toFloat();

            ret.setRgbF(r, g, b);
        }
        else if (type == ColorType::Vec4Type) {
            float r = match.captured(1).toFloat();
            float g = match.captured(2).toFloat();
            float b = match.captured(3).toFloat();
            float a = match.captured(4).toFloat();

            ret.setRgbF(r, g, b, a);
        }
        else if (type == ColorType::HexType) {
            ret.setNamedColor(match.captured());
        }

        Q_ASSERT_X(ret.isValid(), Q_FUNC_INFO, "The color cannot be invalid.");

        return ret;
    }

    /* attributes */
    QMap<ColorType, QRegularExpression> colorRegexes;
};


////////////////////////// ColorWatcher //////////////////////////

ColorWatcher::ColorWatcher(QObject *parent) :
    QObject(parent),
    d(new ColorWatcherImpl)
{

}

ColorWatcher::~ColorWatcher()
{}

void ColorWatcher::processCurrentTextCursor(TextEditorWidget *textEditor)
{
    Q_ASSERT_X(textEditor, Q_FUNC_INFO, "The current editor is invalid.");

    QTextCursor currentCursor = textEditor->textCursor();
    QString lineText = currentCursor.block().text();

    for (auto it = d->colorRegexes.begin(); it != d->colorRegexes.end(); ++it) {
        QRegularExpressionMatchIterator matchIt = it.value().globalMatch(lineText);

        while (matchIt.hasNext()) {
            QRegularExpressionMatch match = matchIt.next();

            int cursorPosInLine = currentCursor.positionInBlock();
            int capturedStart =  match.capturedStart();
            int capturedEnd =  match.capturedEnd();

            bool cursorIsUnderColor = (cursorPosInLine >= capturedStart) &&
                    (cursorPosInLine <= capturedEnd);

            if (cursorIsUnderColor) {
                // If a part of the selection is already selected, deselect it
                if (currentCursor.hasSelection())
                    currentCursor.clearSelection();

                // Select the expression
                currentCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor,
                                           cursorPosInLine - capturedStart);
                currentCursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor,
                                           capturedEnd - capturedStart);

                textEditor->setTextCursor(currentCursor);

                //
                ColorType type = it.key();
                QColor color = d->parseColor(type, match);

                emit colorFound(color, type);
                break;
            }
        }
    }
}

} // namespace Internal
} // namespace ColorPicker
