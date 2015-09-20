#include "colorwatcher.h"

#include <regex>

#include <QDebug> //REMOVEME
#include <QRegularExpression>
#include <QTextBlock>
#include <QTextCursor>

#include <texteditor/texteditor.h>

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

void ColorWatcher::addEditor(TextEditorWidget *editor)
{
    if (!d->editors.contains(editor))
        d->editors.append(editor);
}

void ColorWatcher::onCursorPositionChanged()
{
    TextEditorWidget *editorWidget = (qobject_cast<TextEditorWidget *>(sender()));
    Q_ASSERT_X(editorWidget, Q_FUNC_INFO, "The current editor is invalid.");
    Q_ASSERT_X(d->editors.contains(editorWidget), Q_FUNC_INFO, "The editor is not watched.");
}

} // namespace Internal
} // namespace ColorPicker
