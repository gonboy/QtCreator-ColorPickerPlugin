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
    ColorPickerPluginImpl(ColorPickerPlugin *qq) :
        q_ptr(qq),
        colorWatcher(new ColorWatcher(qq)),
        colorModifier(new ColorModifier(qq)),
        colorEditor(0),
        generalSettings()
    {}

    ~ColorPickerPluginImpl()
    {}

    /* functions */
    QPoint clampColorEditorPosition(const QPoint &cursorPos, const QRect &rect) const
    {
        QPoint ret;
        ret.ry() = cursorPos.y();

        int colorEditorWidth = colorEditor->width();
        int colorEditorHalfWidth = (colorEditorWidth / 2);

        int posX = cursorPos.x() - colorEditorHalfWidth;
        int widgetRight = rect.right();

        if (posX < 0)
            posX = 0;
        else if ( (cursorPos.x() + colorEditorHalfWidth) > (widgetRight) )
            posX = widgetRight - colorEditorWidth;

        ret.rx() = posX;

        return ret;
    }

    /* variables */
    ColorPickerPlugin *q_ptr;

    ColorWatcher *colorWatcher;
    ColorModifier *colorModifier;
    ColorEditor *colorEditor;

    GeneralSettings generalSettings;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERPLUGIN_P_H
