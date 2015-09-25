#ifndef COLORPICKER_GLOBAL
#define COLORPICKER_GLOBAL

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

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKER_GLOBAL

