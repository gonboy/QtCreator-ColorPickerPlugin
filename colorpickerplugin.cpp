#include "colorpickerplugin.h"
#include "colorpickerplugin_p.h"

// Qt includes
#include <QMenu>

// QtCreator includes
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/editormanager/editormanager.h>
#include <coreplugin/editormanager/ieditor.h>

#include <extensionsystem/pluginmanager.h>

#include <texteditor/texteditor.h>

#include <utils/theme/theme.h>

// Plugin includes
#include "colorpickeroptionspage.h"
#include "colorpickerconstants.h"

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorPickerPlugin //////////////////////////

ColorPickerPlugin::ColorPickerPlugin() :
    d(new ColorPickerPluginImpl(this))
{
}

ColorPickerPlugin::~ColorPickerPlugin()
{}

bool ColorPickerPlugin::initialize(const QStringList & /* arguments */, QString * /* errorMessage */)
{
    ColorPickerOptionsPage *optionsPage = new ColorPickerOptionsPage;
    d->generalSettings = optionsPage->generalSettings();

    connect(optionsPage, &ColorPickerOptionsPage::generalSettingsChanged,
            this, &ColorPickerPlugin::onGeneralSettingsChanged);

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

    // Register objects
    addAutoReleasedObject(optionsPage);

    return true;
}

void ColorPickerPlugin::extensionsInitialized()
{
    d->colorEditor = new ColorEditor; // no parent

    // Create connections between internal objects
    connect(d->colorEditor, &ColorEditor::colorChanged,
            [=](const QColor &color) {
        d->colorModifier->insertColor(color, d->colorEditor->outputFormat());
    });

    connect(d->colorEditor, &ColorEditor::outputFormatChanged,
            [=](ColorFormat format) {
        d->colorModifier->insertColor(d->colorEditor->color(), format);
    });
}

void ColorPickerPlugin::onColorEditTriggered()
{
    IEditor *currentEditor = EditorManager::instance()->currentEditor();
    if (!currentEditor)
        return;

    TextEditorWidget *editorWidget = qobject_cast<TextEditorWidget *>(currentEditor->widget());

    if (editorWidget) {
        ColorExpr toEdit = d->colorWatcher->processCurrentTextCursor(editorWidget);

        if (toEdit.value.isValid()) {
            d->colorEditor->setOutputFormat(toEdit.format);
            d->colorEditor->setColor(toEdit.value);
        } else {
            d->colorEditor->setColor(d->colorEditor->color());
        }

        QWidget *editorViewport = editorWidget->viewport();

        d->colorEditor->setParent(editorViewport);
        d->colorEditor->move(d->clampColorEditorPosition(toEdit.pos, editorViewport->rect()));

        d->colorEditor->show();
    }
}

void ColorPickerPlugin::onGeneralSettingsChanged(const GeneralSettings &gs)
{
    d->generalSettings = gs;
}

} // namespace Internal
} // namespace ColorPicker
