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

static QMap<ColorFormat, QRegularExpression> colorRegexes
{
    { ColorFormat::QCssRgbFormat, Constants::REGEX_QCSS_RGB_01 },
    { ColorFormat::QCssRgbPercentFormat, Constants::REGEX_QCSS_RGB_02 },
    { ColorFormat::QCssRgbaAlphaPercentFormat, Constants::REGEX_QCSS_RGBA_01},
    { ColorFormat::QCssRgbaAlphaFloatFormat, Constants::REGEX_QCSS_RGBA_02 },
    { ColorFormat::QssHsvFormat, Constants::REGEX_QSS_HSV },
    { ColorFormat::QssHsvaFormat, Constants::REGEX_QSS_HSVA },
    { ColorFormat::CssHslFormat, Constants::REGEX_CSS_HSL },
    { ColorFormat::CssHslaFormat, Constants::REGEX_CSS_HSLA },
    { ColorFormat::QmlRgbaFormat, Constants::REGEX_QML_RGBA },
    { ColorFormat::QmlHslaFormat, Constants::REGEX_QML_HSLA },
    { ColorFormat::Vec3Format, Constants::REGEX_VEC3 },
    { ColorFormat::Vec4Format, Constants::REGEX_VEC4 },
    { ColorFormat::HexFormat, Constants::REGEX_HEXCOLOR }
};


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
};

ColorWatcherImpl::ColorWatcherImpl() :
    watched(nullptr)
{}

ColorWatcherImpl::~ColorWatcherImpl() {}

QColor ColorWatcherImpl::parseColor(ColorFormat type, const QRegularExpressionMatch &match) const
{
    QColor ret;

    if (type == ColorFormat::QCssRgbFormat) {
        int r = match.captured(1).toInt();
        int g = match.captured(2).toInt();
        int b = match.captured(3).toInt();

        ret.setRgb(r, g, b);
    }
    if (type == ColorFormat::QCssRgbPercentFormat) {
        int r = match.captured(1).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;
        int g = match.captured(2).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;
        int b = match.captured(3).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;

        ret.setRgb(r, g, b);
    }
    else if (type == ColorFormat::QCssRgbaAlphaPercentFormat) {
        ret.setRed(match.captured(1).toInt());
        ret.setGreen(match.captured(2).toInt());
        ret.setBlue(match.captured(3).toInt());
        ret.setAlphaF(match.captured(4).remove(QChar::fromLatin1('%')).toFloat() / 100);
    }
    else if (type == ColorFormat::QCssRgbaAlphaFloatFormat) {
        ret.setRed(match.captured(1).toInt());
        ret.setGreen(match.captured(2).toInt());
        ret.setBlue(match.captured(3).toInt());
        ret.setAlphaF(match.captured(4).toFloat());
    }
    else if (type == ColorFormat::QssHsvFormat) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal v = match.captured(3).toDouble();

        ret.setHsvF(h / 359, s / 255, v / 255);
    }
    else if (type == ColorFormat::QssHsvaFormat) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal v = match.captured(3).toDouble();

        QString alphaString = match.captured(4).remove(QChar::fromLatin1('%'));
        qreal a = alphaString.toDouble() / 100;

        ret.setHsvF(h / 359, s / 255, v / 255, a);
    }
    else if (type == ColorFormat::CssHslFormat) {
        qreal h = match.captured(1).toDouble() / 359;
        qreal s = match.captured(2).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal l = match.captured(3).remove(QChar::fromLatin1('%')).toDouble() / 100;

        ret.setHslF(h, s, l);
    }
    else if (type == ColorFormat::CssHslaFormat) {
        qreal h = match.captured(1).toDouble() / 359;
        float s = match.captured(2).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal l = match.captured(3).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal a = match.captured(4).toDouble();

        ret.setHslF(h, s, l, a);
    }
    else if (type == ColorFormat::QmlRgbaFormat) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setRgbF(r, g, b, a);
    }
    else if (type == ColorFormat::QmlHslaFormat) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal l = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setHslF(h, s, l, a);
    }
    else if (type == ColorFormat::Vec3Format) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();

        ret.setRgbF(r, g, b);
    }
    else if (type == ColorFormat::Vec4Format) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setRgbF(r, g, b, a);
    }
    else if (type == ColorFormat::HexFormat) {
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

    for (auto it = colorRegexes.begin(); it != colorRegexes.end(); ++it) {
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
