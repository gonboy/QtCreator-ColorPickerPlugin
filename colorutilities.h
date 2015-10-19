#ifndef COLORUTILITIES_H
#define COLORUTILITIES_H

#include <QColor>
#include <QPoint>

namespace ColorPicker {
namespace Internal {

enum ColorCategory
{
    AnyCategory,
    QssCategory,
    CssCategory,
    QmlCategory,
    GlslCategory
};

enum ColorFormat
{
    // Qss-Css common
    QCssRgbFormat,                // rgb(255, 255, 255)
    QCssRgbPercentFormat,         // rgb(100%, 100%, 100%)
    QCssRgbaAlphaFloatFormat,     // rgba(255, 255, 255, 1.0)
    QCssRgbaAlphaPercentFormat,   // rgba(255, 255, 255, 100%)
    // Qss specific
    QssHsvFormat,                 // hsv(359, 255, 255)
    QssHsvaFormat,                // hsva(359, 255, 255, 100%)
    // Css specific
    CssHslFormat,                 // hsl(359, 100%, 100%)
    CssHslaFormat,                // hsla(359, 100%, 100%, 1.0)
    // Qml
    QmlRgbaFormat,                // Qt.rgba(1.0, 1.0, 1.0, 1.0)
    QmlHslaFormat,                // Qt.hsla(1.0, 1.0, 1.0, 1.0)
    // Glsl
    Vec3Format,                   // vec3(1.0, 1.0, 1.0)
    Vec4Format,                   // vec4(1.0, 1.0, 1.0, 1.0)
    // Others
    HexFormat                     // #FFFFFFFFFFFF | #FFFFFFFFF | #FFFFFFFF | #FFFFFF | #FFF
};

typedef QSet<ColorFormat> ColorFormatSet;

struct ColorExpr
{
    ColorFormat format;
    QColor value;
    QPoint pos;
};

QColor parseColor(ColorFormat format, const QRegularExpressionMatch &match);
QString colorFormatToPrefix(ColorFormat type);
QString colorToString(const QColor &color, ColorFormat format);

} // namespace Internal
} // namespace ColorPicker

#endif // COLORUTILITIES_H

