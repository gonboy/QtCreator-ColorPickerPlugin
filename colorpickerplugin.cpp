#include "colorpickerplugin.h"

#include <QMenu>

#include <extensionsystem/pluginmanager.h>

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>

#include <texteditor/texteditor.h>

#include "colorwatcher.h"

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {

ColorPickerPlugin::ColorPickerPlugin() :
    m_colorWatcher(new ColorWatcher(this))
{
}

bool ColorPickerPlugin::initialize(const QStringList & /* arguments */, QString * /* errorMessage */)
{
    // Register the plugin actions
    ActionContainer *toolsContainer = ActionManager::actionContainer(Core::Constants::M_TOOLS);

    ActionContainer *myContainer = ActionManager::createMenu("ColorPicker");
    QMenu *myMenu = myContainer->menu();
    myMenu->setTitle(tr("&ColorPicker"));
    myMenu->setEnabled(true);

    toolsContainer->addMenu(myContainer);

    // Connect to the core system
    connect(EditorManager::instance(), &EditorManager::currentEditorChanged,
            this, &ColorPickerPlugin::onCurrentEditorChanged);

    connect(EditorManager::instance(), &EditorManager::editorAboutToClose,
            this, &ColorPickerPlugin::onEditorAboutToClose);

    return true;
}

void ColorPickerPlugin::extensionsInitialized()
{
}

void ColorPickerPlugin::onCurrentEditorChanged(Core::IEditor *editor)
{
    if (!editor)
        return;

    TextEditorWidget *currentTextEditorWidget = qobject_cast<TextEditorWidget *>(editor->widget());
    Q_ASSERT_X(currentTextEditorWidget, Q_FUNC_INFO, "The current editor has no attached widget.");

    m_colorWatcher->addEditor(currentTextEditorWidget);

    connect(currentTextEditorWidget, &TextEditorWidget::cursorPositionChanged,
            m_colorWatcher, &ColorWatcher::onCursorPositionChanged);
}

void ColorPickerPlugin::onEditorAboutToClose(IEditor *editor)
{
    TextEditorWidget *currentTextEditorWidget = qobject_cast<TextEditorWidget *>(editor->widget());
    Q_ASSERT_X(currentTextEditorWidget, Q_FUNC_INFO, "The about to be closed editor has no attached widget.");

    disconnect(currentTextEditorWidget, &TextEditorWidget::cursorPositionChanged,
               m_colorWatcher, &ColorWatcher::onCursorPositionChanged);
}

} // namespace Internal
} // namespace ColorPicker
