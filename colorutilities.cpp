#include "colorutilities.h"

#include <QDebug> // REMOVEME
#include <QRegularExpression>

namespace ColorPicker {
namespace Internal {

QColor parseColor(ColorFormat format, const QRegularExpressionMatch &match)
{
    QColor ret;

    if (format == ColorFormat::QCssRgbUCharFormat) {
        int r = match.captured(1).toInt();
        int g = match.captured(2).toInt();
        int b = match.captured(3).toInt();

        ret.setRgb(r, g, b);

        QString possibleAlpha = match.captured(4);
        if (!possibleAlpha.isNull()) {
            qreal a = possibleAlpha.toDouble();

            ret.setAlphaF(a);
        }
    }
    if (format == ColorFormat::QCssRgbPercentFormat) {
        qreal r = match.captured(1).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal g = match.captured(2).remove(QChar::fromLatin1('%')).toDouble() / 100;
        qreal b = match.captured(3).remove(QChar::fromLatin1('%')).toDouble() / 100;

        ret.setRgbF(r, g, b);

        QString possibleAlpha = match.captured(4);
        if (!possibleAlpha.isNull()) {
            qreal a = possibleAlpha.toDouble();

            ret.setAlphaF(a);
        }
    }
    else if (format == ColorFormat::QssHsvFormat) {
        int h = match.captured(1).toInt();
        int s = match.captured(2).toInt();
        int v = match.captured(3).toInt();

        ret.setHsv(h, s, v);

        QString possibleAlpha = match.captured(4);
        if (!possibleAlpha.isNull()) {
            qreal a = possibleAlpha.remove(QChar::fromLatin1('%')).toDouble() / 100;

            ret.setAlphaF(a);
        }
    }
    else if (format == ColorFormat::CssHslFormat) {
        int h = match.captured(1).toInt();
        int s = match.captured(2).remove(QChar::fromLatin1('%')).toInt() * 255 / 100;
        int l = match.captured(3).remove(QChar::fromLatin1('%')).toInt() * 255 / 100;

        ret.setHsl(h, s, l);

        QString possibleAlpha = match.captured(4);
        if (!possibleAlpha.isNull()) {
            qreal a = possibleAlpha.toDouble();

            ret.setAlphaF(a);
        }
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
    else if (format == ColorFormat::GlslFormat) {
        qreal r = match.captured(1).toDouble();
        qreal g = match.captured(2).toDouble();
        qreal b = match.captured(3).toDouble();

        ret.setRgbF(r, g, b);

        QString possibleAlpha = match.captured(4);
        if (!possibleAlpha.isNull()) {
            qreal a = possibleAlpha.toDouble();

            ret.setAlphaF(a);
        }
    }
    else if (format == ColorFormat::HexFormat) {
        ret.setNamedColor(match.captured());
    }

    Q_ASSERT_X(ret.isValid(), Q_FUNC_INFO, "The color cannot be invalid.");

    return ret;
}

QString colorToString(const QColor &color, ColorFormat format)
{
    QString ret;

    QString prefix;
    QString colorComponents;

    if (format == ColorFormat::QCssRgbUCharFormat) {
        prefix = QLatin1String("rgb(");
        colorComponents = QString::number(color.red()) + QLatin1String(", ")
                + QString::number(color.green()) + QLatin1String(", ")
                + QString::number(color.blue());

        qreal alpha = color.alphaF();
        if (alpha < 1.0) {
            prefix.insert(3, QLatin1Char('a'));
            colorComponents += QLatin1String(", ") + QString::number(color.alphaF());
        }
    }
    if (format == ColorFormat::QCssRgbPercentFormat) {
        int rP = qRound(color.redF() * 100);
        int gP = qRound(color.greenF() * 100);
        int bP = qRound(color.blueF() * 100);

        prefix = QLatin1String("rgb(");
        colorComponents = QString::number(rP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(gP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(bP) + QChar::fromLatin1('%');

        qreal alpha = color.alphaF();

        if (alpha < 1.0) {
            prefix.insert(3, QLatin1Char('a'));
            colorComponents += QLatin1String(", ") + QString::number(alpha);
        }
    }
    else if (format == ColorFormat::QssHsvFormat) {
        prefix = QLatin1String("hsv(");
        colorComponents = QString::number(color.hsvHue()) + QLatin1String(", ")
                + QString::number(color.hsvSaturation()) + QLatin1String(", ")
                + QString::number(color.value());

        int aP = qRound(color.alphaF() * 100);

        if (aP < 100) {
            prefix.insert(3, QLatin1Char('a'));
            colorComponents += QLatin1String(", ") + QString::number(aP);
        }
    }
    else if (format == ColorFormat::CssHslFormat) {
        prefix = QLatin1String("hsl(");

        int sP = qRound(color.hslSaturationF() * 100);
        int lP = qRound(color.lightnessF() * 100);

        colorComponents = QString::number(color.hslHue()) + QLatin1String(", ")
                + QString::number(sP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(lP) + QChar::fromLatin1('%');

        qreal alpha = color.alphaF();
        if (alpha < 1.0) {
            prefix.insert(3, QLatin1Char('a'));
            colorComponents += QLatin1String(", ") + QString::number(color.alphaF());
        }
    }
    else if (format == ColorFormat::QmlRgbaFormat) {
        prefix = QLatin1String("Qt.rgba(");
        colorComponents = QString::number(color.redF()) + QLatin1String(", ")
                + QString::number(color.greenF()) + QLatin1String(", ")
                + QString::number(color.blueF()) + QLatin1String(", ")
                + QString::number(color.alphaF());
    }
    else if (format == ColorFormat::QmlHslaFormat) {
        prefix = QLatin1String("Qt.hsla(");
        colorComponents = QString::number(color.hueF()) + QLatin1String(", ")
                + QString::number(color.saturationF()) + QLatin1String(", ")
                + QString::number(color.lightnessF()) + QLatin1String(", ")
                + QString::number(color.alphaF());
    }
    else if (format == ColorFormat::GlslFormat) {
        prefix = QLatin1String("vec");

        colorComponents = QString::number(color.redF()) + QLatin1String(", ")
                + QString::number(color.greenF()) + QLatin1String(", ")
                + QString::number(color.blueF());

        qreal alpha = color.alphaF();
        if (alpha < 1.0) {
            prefix.append(QLatin1Char('4'));
            colorComponents += QLatin1String(", ") + QString::number(color.alphaF());
        } else {
            prefix.append(QLatin1Char('3'));
        }

        prefix.append(QLatin1Char('('));
    }
    else if (format == ColorFormat::HexFormat) {
        prefix = QLatin1String("#");
        colorComponents = color.name().toUpper().remove(0, 1);
    }

    Q_ASSERT(!prefix.isNull());
    Q_ASSERT(!colorComponents.isNull());

    ret = prefix + colorComponents;

    if (format != ColorFormat::HexFormat)
        ret += QChar::fromLatin1(')');

    Q_ASSERT_X(!ret.isNull(), Q_FUNC_INFO, "The string version of the color is invalid");

    return ret;
}

} // namespace Internal
} // namespace ColorPicker
