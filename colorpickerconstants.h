#ifndef COLORPICKERCONSTANTS_H
#define COLORPICKERCONSTANTS_H

#include <string>

#include <QRegularExpression>

#define DECL_QREGEX_CONSTANT(name, regex) \
    const QRegularExpression name(QString::fromStdString(regex), \
    QRegularExpression::CaseInsensitiveOption)

namespace ColorPicker {
namespace Internal {
namespace Constants {


////////////////////////// Actions //////////////////////////

const char COLORPICKER_SETTINGS_ID[] = "ColorPicker.Settings";
const char COLORPICKER_SETTINGS_PREFIX[] = "colorpickerplugin";
const char COLORPICKER_SETTINGS_DISPLAY_NAME[] = "General";
const char COLORPICKER_SETTINGS_CATEGORY[] = "YW.ColorPicker";
const char COLORPICKER_SETTINGS_TR_CATEGORY[] = QT_TRANSLATE_NOOP("ColorPicker", "ColorPicker");
const char COLORPICKER_SETTINGS_CATEGORY_ICON[]  = ":/colorpicker/images/icon.png";

const char ACTION_NAME_TRIGGER_COLOR_EDIT[] = "Trigger Color Edit";

const char TRIGGER_COLOR_EDIT[] = "ColorPicker.TriggerColorEdit";


////////////////////////// Regex parts //////////////////////////

const std::string _RXPART_0_TO_255 = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
const std::string _RXPART_0_TO_359 = "([0-9]|[1-9][0-9]|[1|2][0-9][0-9]|3[0-5][0-9])";
const std::string _RXPART_PERCENTAGE = "([0-9]|[1-9][0-9]|100)\\%?";
const std::string _RXPART_FLOAT_LITERAL = "([0]?\\.[0-9]*|1\\.0|1|0)[f]";
const std::string _RXPART_FLOAT_VALUE = "(0|1|1.0|0*\\.\\d+)";
const std::string _RXPART_BLANK = "\\s*?";


////////////////////////// Regex //////////////////////////

// Qss-Css colors
DECL_QREGEX_CONSTANT(REGEX_QCSS_RGB_01,
                    "rgb" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK
                    + "\\)");

DECL_QREGEX_CONSTANT(REGEX_QCSS_RGB_02,
                    "rgb" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_PERCENTAGE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_PERCENTAGE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_PERCENTAGE + _RXPART_BLANK
                    + "\\)");

DECL_QREGEX_CONSTANT(REGEX_QCSS_RGBA_01,
                    "rgba" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_PERCENTAGE + _RXPART_BLANK
                    + "\\)");

DECL_QREGEX_CONSTANT(REGEX_QCSS_RGBA_02,
                    "rgba" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK
                    + "\\)");

// Qss colors
DECL_QREGEX_CONSTANT(REGEX_QSS_HSV,
                    "hsv" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_0_TO_359  + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255  + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255 + _RXPART_BLANK
                    + "\\)");

DECL_QREGEX_CONSTANT(REGEX_QSS_HSVA,
                    "hsva" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_0_TO_359 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_0_TO_255  + _RXPART_BLANK + ","  + _RXPART_BLANK
                    + _RXPART_0_TO_255  + _RXPART_BLANK + ","  + _RXPART_BLANK
                    + _RXPART_PERCENTAGE + _RXPART_BLANK
                    + "\\)");

// Css colors
DECL_QREGEX_CONSTANT(REGEX_CSS_HSL,
                    "hsl" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_0_TO_359  + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_PERCENTAGE  + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_PERCENTAGE + _RXPART_BLANK
                    + "\\)");

DECL_QREGEX_CONSTANT(REGEX_CSS_HSLA,
                    "hsla" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_0_TO_359 + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_PERCENTAGE  + _RXPART_BLANK + ","  + _RXPART_BLANK
                    + _RXPART_PERCENTAGE  + _RXPART_BLANK + ","  + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK
                    + "\\)");

// Qml colors
DECL_QREGEX_CONSTANT(REGEX_QML_RGBA,
                    "Qt.rgba" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + _RXPART_BLANK
                    + "\\)");

DECL_QREGEX_CONSTANT(REGEX_QML_HSLA,
                    "Qt.hsla" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + _RXPART_BLANK
                    + "\\)");

// OpenGL colors
DECL_QREGEX_CONSTANT(REGEX_VEC3,
                    "vec3" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK
                    + "\\)");

DECL_QREGEX_CONSTANT(REGEX_VEC4,
                    "vec4" + _RXPART_BLANK
                    + "\\(" + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK + "," + _RXPART_BLANK
                    + _RXPART_FLOAT_VALUE + _RXPART_BLANK
                    + "\\)");

// Other colors
DECL_QREGEX_CONSTANT(REGEX_HEXCOLOR,
                    "(\\#[a-f0-9]{12}|\\#[a-f0-9]{9}|\\#[a-f0-9]{8}|\\#[a-f0-9]{6}|\\#[a-f0-9]{3})");

} // namespace Constants
} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERCONSTANTS_H

