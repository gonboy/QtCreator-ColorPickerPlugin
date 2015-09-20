#ifndef COLORPICKERPLUGIN_H
#define COLORPICKERPLUGIN_H

#include <extensionsystem/iplugin.h>

namespace Core {
class IEditor;
}

namespace ColorPicker {
namespace Internal {

class ColorWatcher;

class ColorPickerPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "ColorPicker.json")

public:
    ColorPickerPlugin();

    virtual bool initialize(const QStringList &arguments, QString *errorMessage);
    virtual void extensionsInitialized();

private slots:
    void onCurrentEditorChanged(Core::IEditor *editor);
    void onEditorAboutToClose(Core::IEditor *editor);

private:
    ColorWatcher *m_colorWatcher;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERPLUGIN_H
