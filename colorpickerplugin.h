#ifndef COLORPICKERPLUGIN_H
#define COLORPICKERPLUGIN_H

#include <extensionsystem/iplugin.h>

namespace Core {
class IEditor;
}

namespace ColorPicker {
namespace Internal {

class ColorDialog;
class ColorModifier;
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
    void onColorEditTriggered();

    // The following tests expect that no projects are loaded on start-up.
    void test_addAndReplaceColor();

private:
    ColorWatcher *m_colorWatcher;
    ColorModifier *m_colorModifier;
    ColorDialog *m_colorDialog;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERPLUGIN_H
