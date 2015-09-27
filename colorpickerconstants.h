#ifndef COLORPICKERCONSTANTS_H
#define COLORPICKERCONSTANTS_H

#include <string>

namespace ColorPicker {
namespace Internal {
namespace Constants {


////////////////////////// Actions //////////////////////////

const char ACTION_NAME_TRIGGER_COLOR_EDIT[] = "Edit color under cursor";

const char TRIGGER_COLOR_EDIT[] = "ColorPicker.TriggerColorEdit";


////////////////////////// Regex parts //////////////////////////

const std::string _RXPART_RGBA_INT = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
const std::string _RXPART_HUE = "([0-9]|[1-9][0-9]|[1|2][0-9][0-9]|3[0-5][0-9]|360)";
const std::string _RXPART_SATURATION_LUMINANCE_VALUE = "([0-9]|[1-9][0-9]|100)";
const std::string _RXPART_FLOAT_LITERAL = "([0]?\\.[0-9]*|1\\.0|1|0)[f]";
const std::string _RXPART_FLOAT_VALUE = "(0|1|1.0|0*\\.\\d+)";
const std::string _RXPART_BLANK_SPACE = "\\s*?";


////////////////////////// Regex //////////////////////////

// Base colors
const std::string REGEX_RGB =
        "rgb" + _RXPART_BLANK_SPACE
        + "\\(" + _RXPART_BLANK_SPACE
        + _RXPART_RGBA_INT + _RXPART_BLANK_SPACE + "," + _RXPART_BLANK_SPACE
        + _RXPART_RGBA_INT + _RXPART_BLANK_SPACE + "," + _RXPART_BLANK_SPACE
        + _RXPART_RGBA_INT + _RXPART_BLANK_SPACE
        + "\\)";

const std::string REGEX_RGBA =
        "rgba" + _RXPART_BLANK_SPACE
        + "\\(" + _RXPART_BLANK_SPACE
        + _RXPART_RGBA_INT + _RXPART_BLANK_SPACE + "," + _RXPART_BLANK_SPACE
        + _RXPART_RGBA_INT + _RXPART_BLANK_SPACE + "," + _RXPART_BLANK_SPACE
        + _RXPART_RGBA_INT + _RXPART_BLANK_SPACE + "," + _RXPART_BLANK_SPACE
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK_SPACE
        + "\\)";

const std::string REGEX_HSV =
        "hsv" + _RXPART_BLANK_SPACE
        + "\\(" + _RXPART_BLANK_SPACE
        + _RXPART_HUE  + _RXPART_BLANK_SPACE + "," + _RXPART_BLANK_SPACE
        + _RXPART_SATURATION_LUMINANCE_VALUE  + _RXPART_BLANK_SPACE + "," + _RXPART_BLANK_SPACE
        + _RXPART_SATURATION_LUMINANCE_VALUE  + _RXPART_BLANK_SPACE
        + "\\)";

const std::string REGEX_HSVA =
        "hsva" + _RXPART_BLANK_SPACE
        + "\\(" + _RXPART_BLANK_SPACE
        + _RXPART_HUE + _RXPART_BLANK_SPACE + "," + _RXPART_BLANK_SPACE
        + _RXPART_SATURATION_LUMINANCE_VALUE  + _RXPART_BLANK_SPACE + ","  + _RXPART_BLANK_SPACE
        + _RXPART_SATURATION_LUMINANCE_VALUE  + _RXPART_BLANK_SPACE + ","  + _RXPART_BLANK_SPACE
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK_SPACE
        + "\\)";

const std::string REGEX_HEXCOLOR = "(\\#[a-f0-9]{6}|\\#[a-f0-9]{3})";

} // namespace Constants
} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERCONSTANTS_H

