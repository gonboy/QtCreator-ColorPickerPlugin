#include "colorutilities.h"

#include <QDebug> // REMOVEME
#include <QRegularExpression>

namespace ColorPicker {
namespace Internal {

QColor parseColor(ColorFormat format, const QRegularExpressionMatch &match)
{
    QColor ret;

    if (format == ColorFormat::QCssRgbFormat) {
        int r = match.captured(1).toInt();
        int g = match.captured(2).toInt();
        int b = match.captured(3).toInt();

        ret.setRgb(r, g, b);
    }
    if (format == ColorFormat::QCssRgbPercentFormat) {
        int r = match.captured(1).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;
        int g = match.captured(2).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;
        int b = match.captured(3).remove(QChar::fromLatin1('%')).toInt() / 100 * 255;

        ret.setRgb(r, g, b);
    }
    else if (format == ColorFormat::QCssRgbaAlphaPercentFormat) {
        ret.setRed(match.captured(1).toInt());
        ret.setGreen(match.captured(2).toInt());
        ret.setBlue(match.captured(3).toInt());
        ret.setAlphaF(match.captured(4).remove(QChar::fromLatin1('%')).toFloat() / 100);
    }
    else if (format == ColorFormat::QCssRgbaAlphaFloatFormat) {
        ret.setRed(match.captured(1).toInt());
        ret.setGreen(match.captured(2).toInt());
        ret.setBlue(match.captured(3).toInt());
        ret.setAlphaF(match.captured(4).toFloat());
    }
    else if (format == ColorFormat::QssHsvFormat) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal v = match.captured(3).toDouble();

        ret.setHsvF(h / 359, s / 255, v / 255);
    }
    else if (format == ColorFormat::QssHsvaFormat) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal v = match.captured(3).toDouble();

        QString alphaString = match.captured(4).remove(QChar::fromLatin1('%'));
        qreal a = alphaString.toDouble() / 100;

        ret.setHsvF(h / 359, s / 255, v / 255, a);
    }
    else if (format == ColorFormat::CssHslFormat) {
        qreal h = match.captured(1).toDouble() / 359;
        qreal s = match.captured(2).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal l = match.captured(3).remove(QChar::fromLatin1('%')).toDouble() / 100;

        ret.setHslF(h, s, l);
    }
    else if (format == ColorFormat::CssHslaFormat) {
        qreal h = match.captured(1).toDouble() / 359;
        float s = match.captured(2).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal l = match.captured(3).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal a = match.captured(4).toDouble();

        ret.setHslF(h, s, l, a);
    }
    else if (format == ColorFormat::QmlRgbaFormat) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setRgbF(r, g, b, a);
    }
    else if (format == ColorFormat::QmlHslaFormat) {
        qreal h = match.captured(1).toDouble();
        qreal s = match.captured(2).toDouble();
        qreal l = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setHslF(h, s, l, a);
    }
    else if (format == ColorFormat::Vec3Format) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();

        ret.setRgbF(r, g, b);
    }
    else if (format == ColorFormat::Vec4Format) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();
        qreal a = match.captured(4).toDouble();

        ret.setRgbF(r, g, b, a);
    }
    else if (format == ColorFormat::HexFormat) {
        ret.setNamedColor(match.captured());
    }

    Q_ASSERT_X(ret.isValid(), Q_FUNC_INFO, "The color cannot be invalid.");

    return ret;
}

QString colorFormatToPrefix(ColorFormat type)
{
    QString ret;

    switch (type) {
    case ColorFormat::QCssRgbFormat:
    case ColorFormat::QCssRgbPercentFormat:
        ret = QLatin1String("rgb(");
        break;
    case ColorFormat::QCssRgbaAlphaPercentFormat:
    case ColorFormat::QCssRgbaAlphaFloatFormat:
        ret = QLatin1String("rgba(");
        break;
    case ColorFormat::QssHsvFormat:
        ret = QLatin1String("hsv(");
        break;
    case ColorFormat::QssHsvaFormat:
        ret = QLatin1String("hsva(");
        break;
    case ColorFormat::CssHslFormat:
        ret = QLatin1String("hsl(");
        break;
    case ColorFormat::CssHslaFormat:
        ret = QLatin1String("hsla(");
        break;
    case ColorFormat::QmlRgbaFormat:
        ret = QLatin1String("Qt.rgba(");
        break;
    case ColorFormat::QmlHslaFormat:
        ret = QLatin1String("Qt.hsla(");
        break;
    case ColorFormat::Vec3Format:
        ret = QLatin1String("vec3(");
        break;
    case ColorFormat::Vec4Format:
        ret = QLatin1String("vec4(");
        break;
        // No ColorType::HexType because of the QColor::name() function
    default:
        break;
    }

    return ret;
}

QString colorToString(const QColor &color, ColorFormat format)
{
    QString ret;

    QString prefix = colorFormatToPrefix(format);
    QString colorComponents;

    if (format == ColorFormat::QCssRgbFormat) {
        colorComponents = QString::number(color.red()) + QLatin1String(", ")
                + QString::number(color.green()) + QLatin1String(", ")
                + QString::number(color.blue());
    }
    if (format == ColorFormat::QCssRgbPercentFormat) {
        int rP = color.red() / 255;
        int gP = color.green() / 255;
        int bP = color.blue() / 255;

        colorComponents = QString::number(rP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(gP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(bP) + QChar::fromLatin1('%');
    }
    else if (format == ColorFormat::QCssRgbaAlphaPercentFormat) {
        int aP = color.alphaF() * 100;

        colorComponents = QString::number(color.red()) + QLatin1String(", ")
                + QString::number(color.green()) + QLatin1String(", ")
                + QString::number(color.blue()) + QLatin1String(", ")
                + QString::number(aP) + QChar::fromLatin1('%');
    }
    else if (format == ColorFormat::QCssRgbaAlphaFloatFormat) {
        colorComponents = QString::number(color.red()) + QLatin1String(", ")
                + QString::number(color.green()) + QLatin1String(", ")
                + QString::number(color.blue()) + QLatin1String(", ")
                + QString::number(color.alphaF());
    }
    else if (format == ColorFormat::QssHsvFormat) {
        colorComponents = QString::number(color.hsvHue()) + QLatin1String(", ")
                + QString::number(color.hsvSaturation()) + QLatin1String(", ")
                + QString::number(color.value());
    }
    else if (format == ColorFormat::QssHsvaFormat) {
        int aP = color.alphaF() * 100;

        colorComponents = QString::number(color.hsvHue()) + QLatin1String(", ")
                + QString::number(color.hsvSaturation()) + QLatin1String(", ")
                + QString::number(color.value()) + QLatin1String(", ")
                + QString::number(aP);
    }
    else if (format == ColorFormat::CssHslFormat) {
        int sP = color.hslSaturation() * 100 / 255;
        int lP = color.lightness() * 100 / 255;

        colorComponents = QString::number(color.hslHue()) + QLatin1String(", ")
                + QString::number(sP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(lP) + QChar::fromLatin1('%');
    }
    else if (format == ColorFormat::CssHslaFormat) {
        int sP = color.hslSaturation() * 100 / 255;
        int lP = color.lightness() * 100 / 255;

        colorComponents = QString::number(color.hslHue()) + QLatin1String(", ")
                + QString::number(sP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(lP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(color.alphaF());
    }
    else if (format == ColorFormat::QmlRgbaFormat) {
        colorComponents = QString::number(color.redF()) + QLatin1String(", ")
                + QString::number(color.greenF()) + QLatin1String(", ")
                + QString::number(color.blueF()) + QLatin1String(", ")
                + QString::number(color.alphaF());
    }
    else if (format == ColorFormat::QmlHslaFormat) {
        colorComponents = QString::number(color.hueF()) + QLatin1String(", ")
                + QString::number(color.saturationF()) + QLatin1String(", ")
                + QString::number(color.lightnessF()) + QLatin1String(", ")
                + QString::number(color.alphaF());
    }
    else if (format == ColorFormat::Vec3Format) {
        colorComponents = QString::number(color.redF()) + QLatin1String(", ")
                + QString::number(color.greenF()) + QLatin1String(", ")
                + QString::number(color.blueF());
    }
    else if (format == ColorFormat::Vec4Format) {
        colorComponents = QString::number(color.redF()) + QLatin1String(", ")
                + QString::number(color.greenF()) + QLatin1String(", ")
                + QString::number(color.blueF()) + QLatin1String(", ")
                + QString::number(color.alphaF());
    }
    else if (format == ColorFormat::HexFormat) {
        colorComponents = color.name().toUpper();
    }

    Q_ASSERT(!colorComponents.isNull());

    ret = prefix + colorComponents;

    if (format != ColorFormat::HexFormat)
        ret += QChar::fromLatin1(')');

    Q_ASSERT_X(!ret.isNull(), Q_FUNC_INFO, "The string version of the color is invalid");

    return ret;
}

} // namespace Internal
} // namespace ColorPicker
