#include "colormodifier.h"

// Qt includes
#include <QDebug>
#include <QTextBlock>
#include <QTextCursor>

// QtCreator includes
#include <coreplugin/editormanager/editormanager.h>

#include <texteditor/texteditor.h>

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorModifierImpl //////////////////////////

class ColorModifierImpl
{
public:
    ColorModifierImpl();

    /* functions */
    QString colorTypeFormat(ColorFormat type) const;

    QString colorToString(const QColor &color, ColorFormat format) const;
};

ColorModifierImpl::ColorModifierImpl()
{

}

QString ColorModifierImpl::colorTypeFormat(ColorFormat type) const
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

QString ColorModifierImpl::colorToString(const QColor &color, ColorFormat format) const
{
    QString ret;

    QString prefix = colorTypeFormat(format);
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
        int sP = color.hslSaturation() / 255 * 100;
        int lP = color.lightness() / 255 * 100;

        colorComponents = QString::number(color.hslHue()) + QLatin1String(", ")
                + QString::number(sP) + QChar::fromLatin1('%') + QLatin1String(", ")
                + QString::number(lP) + QChar::fromLatin1('%');
    }
    else if (format == ColorFormat::CssHslaFormat) {
        int sP = color.hslSaturation() / 255 * 100;
        int lP = color.lightness() / 255 * 100;

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


////////////////////////// ColorModifier //////////////////////////

ColorModifier::ColorModifier(QObject *parent) :
    QObject(parent),
    d(new ColorModifierImpl)
{

}

ColorModifier::~ColorModifier()
{}

void ColorModifier::insertColor(const QColor &newValue, ColorFormat asFormat)
{
    IEditor *currentEditor = EditorManager::instance()->currentEditor();
    if (!currentEditor)
        return;

    TextEditorWidget *editorWidget = qobject_cast<TextEditorWidget *>(currentEditor->widget());
    QTextCursor currentCursor = editorWidget->textCursor();

    QString newText = d->colorToString(newValue, asFormat);

    currentCursor.insertText(newText);
    currentCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor,
                               newText.size());
    currentCursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor,
                               newText.size());

    editorWidget->setTextCursor(currentCursor);
}

} // namespace Internal
} // namespace ColorPicker
