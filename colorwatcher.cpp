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

// Plugin includes
#include "colorpickerconstants.h"

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorWatcherImpl //////////////////////////

class ColorWatcherImpl
{
public:
    ColorWatcherImpl();
    ~ColorWatcherImpl();

    /* functions */
    QColor parseColor(ColorFormat type, const QRegularExpressionMatch &match) const;

    /* variables */
    TextEditor::TextEditorWidget *watched;
    QMap<ColorFormat, QRegularExpression> colorRegexes;
};

ColorWatcherImpl::ColorWatcherImpl() :
    watched(0),
    colorRegexes()
{
    // Register regexes
    colorRegexes.insert(ColorFormat::QCssRgbType, Constants::REGEX_QCSS_RGB_01);
    colorRegexes.insert(ColorFormat::QCssRgbPercentType, Constants::REGEX_QCSS_RGB_02);
    colorRegexes.insert(ColorFormat::QCssRgbaAlphaPercentType, Constants::REGEX_QCSS_RGBA_01);
    colorRegexes.insert(ColorFormat::QCssRgbaAlphaFloatType, Constants::REGEX_QCSS_RGBA_02);
    colorRegexes.insert(ColorFormat::QssHsvType, Constants::REGEX_QSS_HSV);
    colorRegexes.insert(ColorFormat::QssHsvaType, Constants::REGEX_QSS_HSVA);
    colorRegexes.insert(ColorFormat::CssHslType, Constants::REGEX_CSS_HSL);
    colorRegexes.insert(ColorFormat::CssHslaType, Constants::REGEX_CSS_HSLA);
    colorRegexes.insert(ColorFormat::QmlRgbaType, Constants::REGEX_QML_RGBA);
    colorRegexes.insert(ColorFormat::QmlHslaType, Constants::REGEX_QML_HSLA);
    colorRegexes.insert(ColorFormat::Vec3Type, Constants::REGEX_VEC3);
    colorRegexes.insert(ColorFormat::Vec4Type, Constants::REGEX_VEC4);
    colorRegexes.insert(ColorFormat::HexType, Constants::REGEX_HEXCOLOR);
}

ColorWatcherImpl::~ColorWatcherImpl() {}

QColor ColorWatcherImpl::parseColor(ColorFormat type, const QRegularExpressionMatch &match) const
{
    QColor ret;

    if (type == ColorFormat::QCssRgbType) {
        int r = match.captured(1).toInt();
        int g = match.captured(2).toInt();
        int b = match.captured(3).toInt();

        ret.setRgb(r, g, b);
    }
    if (type == ColorFormat::QCssRgbPercentType) {
        int r = match.captured(1).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;
        int g = match.captured(2).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;
        int b = match.captured(3).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;

        ret.setRgb(r, g, b);
    }
    else if (type == ColorFormat::QCssRgbaAlphaPercentType) {
        ret.setRed(match.captured(1).toInt());
        ret.setGreen(match.captured(2).toInt());
        ret.setBlue(match.captured(3).toInt());
        ret.setAlphaF(match.captured(4).remove(QChar::fromLatin1('%')).toFloat() / 100);
    }
    else if (type == ColorFormat::QCssRgbaAlphaFloatType) {
        ret.setRed(match.captured(1).toInt());
        ret.setGreen(match.captured(2).toInt());
        ret.setBlue(match.captured(3).toInt());
        ret.setAlphaF(match.captured(4).toFloat());
    }
    else if (type == ColorFormat::QssHsvType) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal v = match.captured(3).toDouble();

        ret.setHsvF(h / 359, s / 255, v / 255);
    }
    else if (type == ColorFormat::QssHsvaType) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal v = match.captured(3).toDouble();

        QString alphaString = match.captured(4).remove(QChar::fromLatin1('%'));
        qreal a = alphaString.toDouble() / 100;

        ret.setHsvF(h / 359, s / 255, v / 255, a);
    }
    else if (type == ColorFormat::CssHslType) {
        qreal h = match.captured(1).toDouble() / 359;
        qreal s = match.captured(2).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal l = match.captured(3).remove(QChar::fromLatin1('%')).toDouble() / 100;

        ret.setHslF(h, s, l);
    }
    else if (type == ColorFormat::CssHslaType) {
        qreal h = match.captured(1).toDouble() / 359;
        float s = match.captured(2).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal l = match.captured(3).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal a = match.captured(4).toDouble();

        ret.setHslF(h, s, l, a);
    }
    else if (type == ColorFormat::QmlRgbaType) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setRgbF(r, g, b, a);
    }
    else if (type == ColorFormat::QmlHslaType) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal l = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setHslF(h, s, l, a);
    }
    else if (type == ColorFormat::Vec3Type) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();

        ret.setRgbF(r, g, b);
    }
    else if (type == ColorFormat::Vec4Type) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setRgbF(r, g, b, a);
    }
    else if (type == ColorFormat::HexType) {
        ret.setNamedColor(match.captured());
    }

    Q_ASSERT_X(ret.isValid(), Q_FUNC_INFO, "The color cannot be invalid.");

    return ret;
}


////////////////////////// ColorWatcher //////////////////////////

ColorWatcher::ColorWatcher(TextEditorWidget *textEditor) :
    QObject(textEditor),
    d(new ColorWatcherImpl)
{
    Q_ASSERT_X(textEditor, Q_FUNC_INFO, "ColorPickerPlugin > The text editor is invalid.");
    d->watched = textEditor;
}

ColorWatcher::~ColorWatcher()
{
    // disconnect if necessary
}

ColorExpr ColorWatcher::process()
{
    ColorExpr ret;

    QTextCursor currentCursor = d->watched->textCursor();
    QRect cursorRect = d->watched->cursorRect();

    // Search for a color pattern
    QString lineText = currentCursor.block().text();

    for (auto it = d->colorRegexes.begin(); it != d->colorRegexes.end(); ++it) {
        QRegularExpressionMatchIterator matchIt = it.value().globalMatch(lineText);

        if (matchIt.hasNext()) {
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
                cursorRect.setLeft(d->watched->cursorRect(currentCursor).left());
                currentCursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor,
                                           capturedEnd - capturedStart);
                cursorRect.setRight(d->watched->cursorRect(currentCursor).right());

                d->watched->setTextCursor(currentCursor);

                //
                ColorFormat type = it.key();
                QColor color = d->parseColor(type, match);

                ret.format = type;
                ret.value = color;

                break;
            }
        }
    }

    ret.pos = QPoint(cursorRect.center().x(),
                     cursorRect.bottom());

    return ret;
}

} // namespace Internal
} // namespace ColorPicker
