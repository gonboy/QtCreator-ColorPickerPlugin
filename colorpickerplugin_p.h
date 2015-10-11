#ifndef COLORPICKERPLUGIN_P_H
#define COLORPICKERPLUGIN_P_H

#include "colormodifier.h"
#include "colorwatcher.h"
#include "generalsettings.h"

#include "widgets/colordialog.h"

namespace ColorPicker {
namespace Internal {

////////////////////////// ColorPickerPluginImpl //////////////////////////

class ColorPickerPluginImpl
{
public:
    ColorPickerPluginImpl(ColorPickerPlugin *qq) :
        q_ptr(qq),
        colorWatcher(new ColorWatcher(qq)),
        colorModifier(new ColorModifier(qq)),
        colorDialog(new ColorDialog), // no parent for the moment
        generalSettings()
    {}

    /* functions */

    /* variables */
    ColorPickerPlugin *q_ptr;

    ColorWatcher *colorWatcher;
    ColorModifier *colorModifier;
    ColorDialog *colorDialog;

    GeneralSettings generalSettings;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERPLUGIN_P_H
