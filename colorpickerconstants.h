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

const std::string _RXPART_0_TO_255 = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
const std::string _RXPART_0_TO_360 = "([0-9]|[1-9][0-9]|[1|2][0-9][0-9]|3[0-5][0-9]|360)";
const std::string _RXPART_PERCENTAGE = "([0-9]|[1-9][0-9]|100)\\%?";
const std::string _RXPART_FLOAT_LITERAL = "([0]?\\.[0-9]*|1\\.0|1|0)[f]";
const std::string _RXPART_FLOAT_VALUE = "(0|1|1.0|0*\\.\\d+)";
const std::string _RXPART_BLANK = "\\s*?";


////////////////////////// Regex //////////////////////////

// Qss-Css colors
const std::string REGEX_QCSS_RGB_01 =
        "rgb" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK
        + "\\)";

const std::string REGEX_QCSS_RGB_02 =
        "rgb" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_PERCENTAGE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_PERCENTAGE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_PERCENTAGE + _RXPART_BLANK
        + "\\)";

const std::string REGEX_QCSS_RGBA_01 =
        "rgba" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_PERCENTAGE + _RXPART_BLANK
        + "\\)";

const std::string REGEX_QCSS_RGBA_02 =
        "rgba" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK
        + "\\)";

// Qss colors
const std::string REGEX_QSS_HSV =
        "hsv" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_0_TO_360  + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255  + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255 + _RXPART_BLANK
        + "\\)";

const std::string REGEX_QSS_HSVA =
        "hsva" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_0_TO_360 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_0_TO_255  + _RXPART_BLANK + ","  + _RXPART_BLANK
        + _RXPART_0_TO_255  + _RXPART_BLANK + ","  + _RXPART_BLANK
        + _RXPART_PERCENTAGE + _RXPART_BLANK
        + "\\)";

// Css colors
const std::string REGEX_CSS_HSL =
        "hsl" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_0_TO_360  + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_PERCENTAGE  + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_PERCENTAGE + _RXPART_BLANK
        + "\\)";

const std::string REGEX_CSS_HSLA =
        "hsla" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_0_TO_360 + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_PERCENTAGE  + _RXPART_BLANK + ","  + _RXPART_BLANK
        + _RXPART_PERCENTAGE  + _RXPART_BLANK + ","  + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK
        + "\\)";

// Qml colors
const std::string REGEX_QML_RGBA =
        "Qt.rgba" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + _RXPART_BLANK
        + "\\)";

const std::string REGEX_QML_HSLA =
        "Qt.hsla" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + _RXPART_BLANK
        + "\\)";

// OpenGL colors
const std::string REGEX_VEC3 =
        "vec3" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK
        + "\\)";

const std::string REGEX_VEC4 =
        "vec4" + _RXPART_BLANK
        + "\\(" + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
        + _RXPART_FLOAT_VALUE + _RXPART_BLANK
        + "\\)";

// Other colors
const std::string REGEX_HEXCOLOR = "(\\#[a-f0-9]{12}|\\#[a-f0-9]{9}|\\#[a-f0-9]{8}|\\#[a-f0-9]{6}|\\#[a-f0-9]{3})";

} // namespace Constants
} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERCONSTANTS_H

