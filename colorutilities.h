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
    QCssRgbUCharFormat,         // rgb(255, 255, 255), rgba(255, 255, 255, 1.0)
    QCssRgbPercentFormat,       // rgb(100%, 100%, 100%) and rgba(100%, 100%, 100%, 1.0)
    // Qss specific
    QssHsvFormat,               // hsv(359, 255, 255) and hsva(359, 255, 255, 100%)
    // Css specific
    CssHslFormat,               // hsl(359, 100%, 100%) and hsla(359, 100%, 100%, 1.0)
    // Qml
    QmlRgbaFormat,              // Qt.rgba(1.0, 1.0, 1.0, 1.0)
    QmlHslaFormat,              // Qt.hsla(1.0, 1.0, 1.0, 1.0)
    // Glsl
    GlslFormat,                 // vec3(1.0, 1.0, 1.0) and vec4(1.0, 1.0, 1.0, 1.0)
    // Others
    HexFormat                   // #FFFFFFFFFFFF | #FFFFFFFFF | #FFFFFFFF | #FFFFFF | #FFF
};

typedef QSet<ColorFormat> ColorFormatSet;

ColorFormatSet formatsFromCategory(ColorCategory category);

struct ColorExpr
{
    ColorFormat format;
    QColor value;
    QPoint pos;
};

QColor parseColor(ColorFormat format, const QRegularExpressionMatch &match);
QString colorToString(const QColor &color, ColorFormat format);

} // namespace Internal
} // namespace ColorPicker

#endif // COLORUTILITIES_H

