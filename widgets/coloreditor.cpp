#include "coloreditor.h"

// Qt includes
#include <QButtonGroup>
#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QPainter>
#include <QPushButton>
#include <QToolButton>
#include <QStyleOption>

// QtCreator includes
#include <coreplugin/coreconstants.h>

#include <utils/theme/theme.h>

// Plugin includes
#include "colorpicker.h"
#include "hueslider.h"
#include "opacityslider.h"

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorEditorImpl //////////////////////////

class ColorEditorImpl
{
public:
    enum UpdateReason
    {
        UpdateFromColorPicker = 1 << 0,
        UpdateFromHueSlider = 1 << 1,
        UpdateFromOpacitySlider = 1 << 2,
        UpdateProgrammatically = 1 << 3,
        UpdateAll = UpdateFromColorPicker | UpdateFromHueSlider | UpdateFromOpacitySlider | UpdateProgrammatically
    };
    Q_DECLARE_FLAGS(UpdateReasons, UpdateReason)

    ColorEditorImpl(ColorEditor *qq) :
        q(qq),
        outputFormat(),
        color(QColor::Hsv),
        colorPicker(new ColorPickerWidget(qq)),
        hueSlider(new HueSlider(qq)),
        opacitySlider(new OpacitySlider(qq)),/*,*/
        btnGroup(new QButtonGroup(qq)),
        rgbBtn(new QPushButton(qq)),
        hslBtn(new QPushButton(qq)),
        hsvBtn(new QPushButton(qq)),
        qmlRgbaBtn(new QPushButton(qq)),
        qmlHslaBtn(new QPushButton(qq)),
        vecBtn(new QPushButton(qq)),
        hexBtn(new QPushButton(qq))
    {}

    /* functions */
    void updateColorWidgets(const QColor &cl, UpdateReasons whichUpdate)
    {
        if (whichUpdate & ColorEditorImpl::UpdateFromColorPicker)
            opacitySlider->setHsv(cl.hsvHue(), cl.hsvSaturation(), cl.value());

        if (whichUpdate & ColorEditorImpl::UpdateFromHueSlider) {
            const QSignalBlocker blocker(colorPicker);

            colorPicker->setColor(cl);
            opacitySlider->setHsv(cl.hsvHue(), cl.hsvSaturation(), cl.value());
        }

        if (whichUpdate & ColorEditorImpl::UpdateFromOpacitySlider) {

        }

        if (whichUpdate & ColorEditorImpl::UpdateProgrammatically) {
            hueSlider->setValueAtomic(cl.hsvHue());
            opacitySlider->setValueAtomic(cl.alpha());
        }
    }

    void setCurrentFormat(ColorFormat f)
    {
        outputFormat = f;

        emit q->outputFormatChanged(f);
    }

    void setCurrentColor(const QColor &cl)
    {
        color = cl;

        emit q->colorChanged(cl);
    }

    QAbstractButton *colorFormatToButton(ColorFormat format) const
    {
        QAbstractButton *ret = 0;

        switch (format) {
        case QCssRgbType:
        case QCssRgbPercentType:
        case QCssRgbaAlphaFloatType:
        case QCssRgbaAlphaPercentType:
            ret = rgbBtn;
            break;
        case QssHsvType:
        case QssHsvaType:
            ret = hsvBtn;
            break;
        case CssHslType:
        case CssHslaType:
            ret = hslBtn;
            break;
        case QmlRgbaType:
            ret = qmlRgbaBtn;
            break;
        case QmlHslaType:
            ret = qmlHslaBtn;
            break;
        case Vec3Type:
        case Vec4Type:
            ret = vecBtn;
            break;
        case HexType:
            ret = hexBtn;
            break;
        default:
            break;
        }

        Q_ASSERT(ret);
        return ret;
    }

    /* variables */
    ColorEditor *q;

    ColorFormat outputFormat;
    QColor color;

    ColorPickerWidget *colorPicker;
    HueSlider *hueSlider;
    OpacitySlider *opacitySlider;

    QButtonGroup *btnGroup;
    QPushButton *rgbBtn;
    QPushButton *hslBtn;
    QPushButton *hsvBtn;
    QPushButton *qmlRgbaBtn;
    QPushButton *qmlHslaBtn;
    QPushButton *vecBtn;
    QPushButton *hexBtn;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ColorEditorImpl::UpdateReasons)


////////////////////////// ColorEditor //////////////////////////

ColorEditor::ColorEditor(QWidget *parent) :
    QFrame(parent),
    d(new ColorEditorImpl(this))
{
    //    setAutoFillBackground(true);
    setFrameShape(QFrame::StyledPanel);

    // Build UI
    // Close button
    auto closeBtn = new QToolButton(this);
    closeBtn->setFixedSize(24, 24);
    closeBtn->setIcon(QIcon(QLatin1String(Core::Constants::ICON_BUTTON_CLOSE)));

    connect(closeBtn, &QToolButton::clicked,
            this, &ColorEditor::close);

    auto leftPanelLayout = new QVBoxLayout;
    leftPanelLayout->addWidget(closeBtn);
    leftPanelLayout->addStretch();

    // Color format selection
    d->rgbBtn->setText(QLatin1String("rgb"));
    d->hslBtn->setText(QLatin1String("hsl"));
    d->hsvBtn->setText(QLatin1String("hsv"));
    d->qmlRgbaBtn->setText(QLatin1String("Qt.rgba"));
    d->qmlHslaBtn->setText(QLatin1String("Qt.hsla"));
    d->vecBtn->setText(QLatin1String("vec"));
    d->hexBtn->setText(QLatin1String("hex"));

    d->rgbBtn->setCheckable(true);
    d->hslBtn->setCheckable(true);
    d->hsvBtn->setCheckable(true);
    d->qmlRgbaBtn->setCheckable(true);
    d->qmlHslaBtn->setCheckable(true);
    d->vecBtn->setCheckable(true);
    d->hexBtn->setCheckable(true);

    // Default checked button
    d->rgbBtn->setChecked(true);

    QGridLayout *formatsLayout = new QGridLayout;
    formatsLayout->addWidget(d->rgbBtn, 0, 0);
    formatsLayout->addWidget(d->hslBtn, 1, 0);
    formatsLayout->addWidget(d->hsvBtn, 2, 0);
    formatsLayout->addWidget(d->qmlRgbaBtn, 3, 0);
    formatsLayout->addWidget(d->qmlHslaBtn, 4, 0);
    formatsLayout->addWidget(d->vecBtn, 5, 0);
    formatsLayout->addWidget(d->hexBtn, 6, 0);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftPanelLayout);
    mainLayout->addSpacing(0);
    mainLayout->addWidget(d->colorPicker);
    mainLayout->addWidget(d->opacitySlider);
    mainLayout->addWidget(d->hueSlider);
    mainLayout->addLayout(formatsLayout);

    // Color format selection logic
    d->btnGroup->addButton(d->rgbBtn);
    d->btnGroup->addButton(d->hslBtn);
    d->btnGroup->addButton(d->hsvBtn);
    d->btnGroup->addButton(d->qmlRgbaBtn);
    d->btnGroup->addButton(d->qmlHslaBtn);
    d->btnGroup->addButton(d->vecBtn);
    d->btnGroup->addButton(d->hexBtn);

    connect(d->btnGroup, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            this, &ColorEditor::onFormatButtonChecked);

    // Color changes logic
    connect(d->colorPicker, &ColorPickerWidget::colorChanged,
            [=](const QColor &newColor) {
        d->updateColorWidgets(newColor, ColorEditorImpl::UpdateFromColorPicker);
        d->setCurrentColor(newColor);
    });

    connect(d->hueSlider, &HueSlider::valueChanged,
            [=](int hue) {
        QColor newColor = QColor::fromHsv(hue,
                                          d->color.hsvSaturation(),
                                          d->color.value(),
                                          d->opacitySlider->value());

        d->updateColorWidgets(newColor,
                              ColorEditorImpl::UpdateFromHueSlider);
        d->setCurrentColor(newColor);
    });

    connect(d->opacitySlider, &OpacitySlider::valueChanged,
            [=](int opacity) {
        QColor newColor = QColor::fromHsv(d->hueSlider->value(),
                                          d->color.hsvSaturation(),
                                          d->color.value(),
                                          opacity);

        d->updateColorWidgets(newColor,
                              ColorEditorImpl::UpdateFromOpacitySlider);
        d->setCurrentColor(newColor);
    });

    setColor(Qt::red);
}

ColorEditor::~ColorEditor()
{}

ColorFormat ColorEditor::outputFormat() const
{
    return d->outputFormat;
}

void ColorEditor::setOutputFormat(ColorFormat format)
{
    if (d->outputFormat != format) {
        const QSignalBlocker blocker(d->btnGroup);

        QAbstractButton *btn = d->colorFormatToButton(format);
        btn->click();

        d->setCurrentFormat(format);
    }
}

QColor ColorEditor::color() const
{
    return d->color;
}

void ColorEditor::setColor(const QColor &color)
{
    if (d->color != color) {
        d->updateColorWidgets(color, ColorEditorImpl::UpdateAll);
        d->setCurrentColor(color);
    }
}

int ColorEditor::hue() const
{
    return d->hueSlider->value();
}

void ColorEditor::setHue(int hue)
{
    Q_ASSERT(hue >= 0 && hue <= 359);

    if (d->hueSlider->value() != hue) {
        d->hueSlider->setValue(hue);

        emit hueChanged(hue);
    }
}

int ColorEditor::opacity() const
{
    return d->opacitySlider->value();
}

void ColorEditor::setOpacity(int opacity)
{
    Q_ASSERT(opacity >= 0 && opacity <= 255);

    if (d->opacitySlider->value() != opacity) {
        d->opacitySlider->setValue(opacity);

        emit opacityChanged(opacity);
    }
}

void ColorEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QStyleOptionFrame opt;
    initStyleOption(&opt);

    Utils::Theme *creatorTheme = Utils::creatorTheme();

    painter.setPen(creatorTheme->color(Utils::Theme::TextColorNormal));
    painter.setBrush(creatorTheme->color(Utils::Theme::BackgroundColorNormal));
    painter.drawRoundedRect(opt.rect.adjusted(0, 0, -1, -1), 3, 3);
}

void ColorEditor::onFormatButtonChecked(QAbstractButton *checkedBtn)
{
    ColorFormat format;

    bool useAlpha = d->color.alphaF() < 1.0f;

    if (checkedBtn == d->rgbBtn) {
        format = (useAlpha) ? ColorFormat::QCssRgbaAlphaFloatType
                            : ColorFormat::QCssRgbType;
    }
    else if (checkedBtn == d->hslBtn) {
        format = (useAlpha) ? ColorFormat::CssHslaType
                            : ColorFormat::CssHslType;
    }
    else if (checkedBtn == d->hsvBtn) {
        format = (useAlpha) ? ColorFormat::QssHsvaType
                            : ColorFormat::QssHsvType;
    }
    else if (checkedBtn == d->qmlRgbaBtn) {
        format = ColorFormat::QmlRgbaType;
    }
    else if (checkedBtn == d->qmlHslaBtn) {
        format = ColorFormat::QmlHslaType;
    }
    else if (checkedBtn == d->vecBtn) {
        format = (useAlpha) ? ColorFormat::Vec3Type
                            : ColorFormat::Vec4Type;
    }
    else if (checkedBtn == d->hexBtn)
        format = ColorFormat::HexType;

    d->setCurrentFormat(format);
}

} // namespace Internal
} // namespace ColorPicker
