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
    ColorWatcherImpl() :
        colorRegexes()
    {
        // Register regexes
        colorRegexes.insert(ColorType::RgbType, Constants::REGEX_RGB);
        colorRegexes.insert(ColorType::RgbaType, Constants::REGEX_RGBA);
        colorRegexes.insert(ColorType::HslType, Constants::REGEX_HSL);
        colorRegexes.insert(ColorType::HslaType, Constants::REGEX_HSLA);
        colorRegexes.insert(ColorType::HsvType, Constants::REGEX_HSV);
        colorRegexes.insert(ColorType::HsvaType, Constants::REGEX_HSVA);
        colorRegexes.insert(ColorType::HexType, Constants::REGEX_HEXCOLOR);
        colorRegexes.insert(ColorType::Vec3Type, Constants::REGEX_VEC3);
        colorRegexes.insert(ColorType::Vec4Type, Constants::REGEX_VEC4);
        colorRegexes.insert(ColorType::QColorInlineCtorRgbType, Constants::REGEX_QCOLOR_INLINE_CTOR_RGB);
    }

    ~ColorWatcherImpl() {}

    QMap<ColorType, std::string> colorRegexes;
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

    for(std::string rawRegex : d->colorRegexes) {
        QRegularExpression regexp(QString::fromStdString(rawRegex),
                                  QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatchIterator it = regexp.globalMatch(lineText);

        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();

            int cursorPosInLine = currentCursor.positionInBlock();

            bool cursorIsUnderColor = (cursorPosInLine >= match.capturedStart()) &&
                    (cursorPosInLine <= match.capturedEnd());

            if (cursorIsUnderColor) {
                //TODO Process the captured color
                break;
            }
        }
    }
}

} // namespace Internal
} // namespace ColorPicker
