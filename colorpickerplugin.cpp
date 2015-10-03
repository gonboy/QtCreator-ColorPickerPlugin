#include "colorpickerplugin.h"

// Qt includes
#include <QMenu>

// QtCreator includes
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>

#include <extensionsystem/pluginmanager.h>

#include <texteditor/texteditor.h>

// Plugin includes
#include "colormodifier.h"
#include "colorpickerconstants.h"
#include "colorwatcher.h"

#include "widgets/colordialog.h"

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorPickerPlugin //////////////////////////

ColorPickerPlugin::ColorPickerPlugin() :
    m_colorWatcher(new ColorWatcher(this)),
    m_colorModifier(new ColorModifier(this)),
    m_colorDialog(new ColorDialog) // no parent for the moment
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

    auto triggerColorEditAction = new QAction(tr(Constants::ACTION_NAME_TRIGGER_COLOR_EDIT), this);
    Command *command = ActionManager::registerAction(triggerColorEditAction,
                                                     Constants::TRIGGER_COLOR_EDIT);
    command->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+C")));

    myContainer->addAction(command);

    connect(triggerColorEditAction, &QAction::triggered,
            this, &ColorPickerPlugin::onColorEditTriggered);

    toolsContainer->addMenu(myContainer);

    return true;
}

void ColorPickerPlugin::extensionsInitialized()
{
}

void ColorPickerPlugin::onColorEditTriggered()
{
    IEditor *currentEditor = EditorManager::instance()->currentEditor();
    if (!currentEditor)
        return;

    TextEditorWidget *editorWidget = qobject_cast<TextEditorWidget *>(currentEditor->widget());

    if (editorWidget) {
        ColorExpr toEdit = m_colorWatcher->processCurrentTextCursor(editorWidget);

        if (toEdit.value.isValid()) {
            m_colorDialog->setColor(toEdit.value);
        }

        m_colorDialog->setParent(editorWidget);
        m_colorDialog->move(toEdit.pos);
        m_colorDialog->show();
    }
}

} // namespace Internal
} // namespace ColorPicker
