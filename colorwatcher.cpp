#include "colorwatcher.h"

#include <QDebug> //REMOVEME

#include <texteditor/texteditor.h>

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorWatcherImpl //////////////////////////

class ColorWatcherImpl
{
public:
    ColorWatcherImpl() :
        editors()
    {

    }

    QList<TextEditorWidget *> editors;
};


////////////////////////// ColorWatcher //////////////////////////

ColorWatcher::ColorWatcher(QObject *parent) :
    QObject(parent),
    d(new ColorWatcherImpl)
{

}

void ColorWatcher::onCursorPositionChanged()
{
    TextEditorWidget *editorWidget = (qobject_cast<TextEditorWidget *>(sender()));
    Q_ASSERT_X(editorWidget, Q_FUNC_INFO, "The current editor is invalid.");
}

} // namespace ColorPicker
} // namespace Internal
