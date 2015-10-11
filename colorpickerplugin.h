#ifndef COLORPICKERPLUGIN_H
#define COLORPICKERPLUGIN_H

#include <extensionsystem/iplugin.h>

namespace Core {
class IEditor;
}

namespace ColorPicker {
namespace Internal {

class ColorPickerPluginImpl;
class GeneralSettings;

class ColorPickerPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "ColorPicker.json")

public:
    ColorPickerPlugin();
    ~ColorPickerPlugin();

    virtual bool initialize(const QStringList &arguments, QString *errorMessage);
    virtual void extensionsInitialized();

private slots:
    void onColorEditTriggered();
    void onGeneralSettingsChanged(const GeneralSettings &gs);

    // The following tests expect that no projects are loaded on start-up.
    void test_addAndReplaceColor();

private:
    QScopedPointer<ColorPickerPluginImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERPLUGIN_H
