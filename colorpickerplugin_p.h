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
        colorDialog(0),
        generalSettings()
    {}

    ~ColorPickerPluginImpl()
    {}

    /* functions */
    QPoint clampColorDialogPosition(const QPoint &cursorPos, const QRect &rect) const
    {
        QPoint ret;
        ret.ry() = cursorPos.y();

        int colorDialogWidth = colorDialog->width();
        int colorDialogHalfWidth = (colorDialogWidth / 2);

        int posX = cursorPos.x() - colorDialogHalfWidth;
        int widgetRight = rect.right();

        if (posX < 0)
            posX = 0;
        else if ( (cursorPos.x() + colorDialogHalfWidth) > (widgetRight) )
            posX = widgetRight - colorDialogWidth;

        ret.rx() = posX;

        return ret;
    }

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
