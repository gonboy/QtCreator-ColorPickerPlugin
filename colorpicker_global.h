#ifndef COLORPICKER_GLOBAL
#define COLORPICKER_GLOBAL

#include <QColor>

namespace ColorPicker {
namespace Internal {

enum ColorType
{
    RgbType,
    RgbaType,
    HslType,
    HslaType,
    HsvType,
    HsvaType,
    HexType,
    Vec3Type,
    Vec4Type,
    QColorInlineCtorRgbType,
};

struct ColorExpr
{
    ColorType type;
    QColor value;
    int line;
    int start;
    int end;

    bool operator==(const ColorExpr &other) const
    {
        if (type != other.type)
            return false;

        if (value != other.value)
            return false;

        if (line != other.line)
            return false;

        if (start != other.start)
            return false;

        if (end != other.end)
            return false;

        return true;
    }

    bool operator!=(const ColorExpr &other) const
    {
        return !(operator ==(other));
    }
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKER_GLOBAL

