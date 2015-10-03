#ifndef COLORPICKER_GLOBAL
#define COLORPICKER_GLOBAL

#include <QColor>
#include <QMetaType>
#include <QPoint>

namespace ColorPicker {
namespace Internal {

enum ColorType
{
    // Qss-Css common
    QCssRgbType,                // rgb(255, 255, 255)
    QCssRgbPercentType,         // rgb(100%, 100%, 100%)
    QCssRgbaAlphaPercentType,   // rgba(255, 255, 255, 100%)
    QCssRgbaAlphaFloatType,     // rgba(255, 255, 255, 1.0)
    // Qss specific
    QssHsvType,                 // hsv(359, 255, 255)
    QssHsvaType,                // hsva(359, 255, 255, 100%)
    // Css specific
    CssHslType,                 // hsl(359, 100%, 100%)
    CssHslaType,                // hsla(359, 100%, 100%, 1.0)
    // Qml
    QmlRgbaType,                // Qt.rgba(1.0, 1.0, 1.0, 1.0)
    QmlHslaType,                // Qt.hsla(1.0, 1.0, 1.0, 1.0)
    // OpenGL
    Vec3Type,                   // vec3(1.0, 1.0, 1.0)
    Vec4Type,                   // vec4(1.0, 1.0, 1.0, 1.0)
    // Others
    HexType                     // #FFFFFFFFFFFF | #FFFFFFFFF | #FFFFFFFF | #FFFFFF | #FFF
};

struct ColorExpr
{
    ColorType type;
    QColor value;
    QPoint pos;
};

} // namespace Internal
} // namespace ColorPicker

Q_DECLARE_METATYPE(ColorPicker::Internal::ColorType)

#endif // COLORPICKER_GLOBAL

