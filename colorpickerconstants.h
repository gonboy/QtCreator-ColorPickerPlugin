#ifndef COLORPICKERCONSTANTS_H
#define COLORPICKERCONSTANTS_H

#include <string>

namespace ColorPicker {
namespace Internal {
namespace Constants {


////////////////////////// Actions //////////////////////////

const char ACTION_NAME_TRIGGER_COLOR_EDIT[] = "Trigger Color Edit";

const char TRIGGER_COLOR_EDIT[] = "ColorPicker.TriggerColorEdit";


////////////////////////// Regex parts //////////////////////////

const std::string _RXPART_RGBA_INT = "\\s*?([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
const std::string _RXPART_HUE = "\\s*([0-9]|[1-9][0-9]|[1|2][0-9][0-9]|3[0-5][0-9]|360)";
const std::string _RXPART_SATURATION_LUMINANCE_VALUE = "\\s*?,\\s*?([0-9]|[1-9][0-9]|100)";
const std::string _RXPART_FLOAT_LITERAL = "\\s*?([0]?\\.[0-9]*|1\\.0|1|0)[f]";
const std::string _RXPART_FLOAT_VALUE = "\\s*?(0|1|1.0|0*\\.\\d+)";


////////////////////////// Regex //////////////////////////

// Base colors
const std::string REGEX_RGB = "rgb\\s*?\\(" + _RXPART_RGBA_INT + "\\s*?," + _RXPART_RGBA_INT + "\\s*?," + _RXPART_RGBA_INT + "\\s*?\\)";
const std::string REGEX_RGBA = "rgba\\s*?\\(" + _RXPART_RGBA_INT + "\\s*?," + _RXPART_RGBA_INT + "\\s*?," + _RXPART_RGBA_INT + "\\s*?," + _RXPART_FLOAT_VALUE + "\\s*?\\)";
const std::string REGEX_HSL = "hsl\\s*?\\(" + _RXPART_HUE + _RXPART_SATURATION_LUMINANCE_VALUE + "\\%?" + _RXPART_SATURATION_LUMINANCE_VALUE + "\\%?\\s*\\)";
const std::string REGEX_HSLA = "hsla\\s*?\\(" + _RXPART_HUE + _RXPART_SATURATION_LUMINANCE_VALUE + "\\%?" + _RXPART_SATURATION_LUMINANCE_VALUE + "\\%?\\s*?," + _RXPART_FLOAT_VALUE + "\\s*?\\)";
const std::string REGEX_HSV = "hsv\\s*?\\(" + _RXPART_HUE + _RXPART_SATURATION_LUMINANCE_VALUE + "\\%?" + _RXPART_SATURATION_LUMINANCE_VALUE + "\\%?\\s*\\)";
const std::string REGEX_HSVA = "hsva\\s*?\\(" + _RXPART_HUE + _RXPART_SATURATION_LUMINANCE_VALUE + "\\%?" + _RXPART_SATURATION_LUMINANCE_VALUE + "\\%?\\s*?," + _RXPART_FLOAT_VALUE + "\\s*?\\)";
const std::string REGEX_HEXCOLOR = "(\\#[a-f0-9]{6}|\\#[a-f0-9]{3})";
const std::string REGEX_VEC3 = "vec3\\s*?\\(" + _RXPART_FLOAT_LITERAL + "?\\s*?\\," + _RXPART_FLOAT_LITERAL + "?\\s*?\\," + _RXPART_FLOAT_LITERAL + "?\\s*?\\)";
const std::string REGEX_VEC4 = "vec4\\s*?\\(" + _RXPART_FLOAT_LITERAL + "?\\s*?\\," + _RXPART_FLOAT_LITERAL + "?\\s*?\\," + _RXPART_FLOAT_LITERAL + "?\\s*?\\," + _RXPART_FLOAT_LITERAL + "?\\s*?\\)";

// Qt colors
const std::string REGEX_QCOLOR_INLINE_CTOR_RGB = "QColor\\s*?\\(" + _RXPART_RGBA_INT + "\\s*?," + _RXPART_RGBA_INT + "\\s*?," + _RXPART_RGBA_INT + "\\s*?(|(," + _RXPART_RGBA_INT + "))\\s*?\\)";
const std::string REGEX_QCOLOR_STATIC_CTOR_RGB = "";
const std::string REGEX_QCOLOR_FROM_HSL = "";
const std::string REGEX_QCOLOR_FROM_HSLA = "";
const std::string REGEX_QCOLOR_FROM_HSV = "";
const std::string REGEX_QCOLOR_FROM_HSVA = "";
const std::string REGEX_QCOLOR_FROM_RGB = "";
const std::string REGEX_QCOLOR_FROM_RGBA = "";

} // namespace Constants
} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERCONSTANTS_H

