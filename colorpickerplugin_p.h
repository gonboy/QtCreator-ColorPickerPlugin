#ifndef COLORPICKERPLUGIN_P_H
#define COLORPICKERPLUGIN_P_H

#include "colormodifier.h"
#include "colorwatcher.h"
#include "generalsettings.h"

#include "widgets/coloreditor.h"

namespace ColorPicker {
namespace Internal {

////////////////////////// ColorPickerPluginImpl //////////////////////////

class ColorPickerPluginImpl
{
public:
    ColorPickerPluginImpl(ColorPickerPlugin *qq);
    ~ColorPickerPluginImpl();

    /* functions */
    ColorCategory colorCategoryForEditor(Core::IEditor *editor) const;

    QPoint clampColorEditorPosition(const QPoint &cursorPos, const QRect &rect) const;

    /* variables */
    ColorPickerPlugin *q;

    QMap<Core::IEditor *, ColorWatcher *> watchers;
    ColorModifier *colorModifier;
    ColorEditor *colorEditor;

    GeneralSettings generalSettings;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERPLUGIN_P_H
