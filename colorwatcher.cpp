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

    /* variables */
    TextEditor::TextEditorWidget *watched;
};

ColorWatcherImpl::ColorWatcherImpl() :
    watched(nullptr)
{}

ColorWatcherImpl::~ColorWatcherImpl() {}


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
                QColor color = parseColor(type, match);

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
