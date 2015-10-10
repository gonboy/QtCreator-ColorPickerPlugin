#include "colordialog.h"

#include <QButtonGroup>
#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>

#include "colorpicker.h"
#include "hueslider.h"
#include "opacityslider.h"

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorDialogImpl //////////////////////////

class ColorDialogImpl
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

    ColorDialogImpl(ColorDialog *qq) :
        q_ptr(qq),
        outputColorFormat(),
        outputColor(QColor::Hsv),
        colorPicker(new ColorPickerWidget(q_ptr)),
        hueSlider(new HueSlider(q_ptr)),
        opacitySlider(new OpacitySlider(q_ptr)),/*,*/
        //        d->colorFrame(new QFrame(q_ptr))
        rgbBtn(new QPushButton(q_ptr)),
        rgbAlphaBtn(new QPushButton(q_ptr)),
        rgbPercentBtn(new QPushButton(q_ptr)),
        hslBtn(new QPushButton(q_ptr)),
        hslAlphaBtn(new QPushButton(q_ptr)),
        hsvBtn(new QPushButton(q_ptr)),
        hsvAlphaBtn(new QPushButton(q_ptr)),
        qmlRgbaBtn(new QPushButton(q_ptr)),
        qmlHslaBtn(new QPushButton(q_ptr)),
        vec3Btn(new QPushButton(q_ptr)),
        vec4Btn(new QPushButton(q_ptr)),
        hexBtn(new QPushButton(q_ptr))
    {}

    /* functions */
    void updateColorWidgets(const QColor &color, UpdateReasons whichUpdate)
    {
        if (whichUpdate & ColorDialogImpl::UpdateFromColorPicker)
            opacitySlider->setHsv(color.hsvHue(), color.hsvSaturation(), color.value());

        if (whichUpdate & ColorDialogImpl::UpdateFromHueSlider) {
            const QSignalBlocker blocker(colorPicker);

            colorPicker->setColor(color);
            opacitySlider->setHsv(color.hsvHue(), color.hsvSaturation(), color.value());
        }

        if (whichUpdate & ColorDialogImpl::UpdateFromOpacitySlider) {

        }

        if (whichUpdate & ColorDialogImpl::UpdateProgrammatically) {
            hueSlider->setValueAtomic(color.hsvHue());
            opacitySlider->setValueAtomic(color.alpha());
        }

        outputColor = color;

        emit q_ptr->colorChanged(color);
    }

    /* variables */
    ColorDialog *q_ptr;

    ColorFormat outputColorFormat;
    QColor outputColor;

    ColorPickerWidget *colorPicker;
    HueSlider *hueSlider;
    OpacitySlider *opacitySlider;
    //    QFrame *d->colorFrame;

    QPushButton *rgbBtn;
    QPushButton *rgbAlphaBtn;
    QPushButton *rgbPercentBtn;
    QPushButton *hslBtn;
    QPushButton *hslAlphaBtn;
    QPushButton *hsvBtn;
    QPushButton *hsvAlphaBtn;
    QPushButton *qmlRgbaBtn;
    QPushButton *qmlHslaBtn;
    QPushButton *vec3Btn;
    QPushButton *vec4Btn;
    QPushButton *hexBtn;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ColorDialogImpl::UpdateReasons)


////////////////////////// ColorDialog //////////////////////////

ColorDialog::ColorDialog(QWidget *parent) :
    QWidget(parent),
    d(new ColorDialogImpl(this))
{
    //    d->colorFrame->setFixedSize(50, 50);

    // Build UI
    d->rgbBtn->setText(QLatin1String("RGB"));
    d->rgbAlphaBtn->setText(QLatin1String("A"));
    d->rgbPercentBtn->setText(QLatin1String("%"));

    d->hslBtn->setText(QLatin1String("HSL"));
    d->hslAlphaBtn->setText(QLatin1String("A"));

    d->hsvBtn->setText(QLatin1String("HSV"));
    d->hsvAlphaBtn->setText(QLatin1String("A"));

    d->qmlRgbaBtn->setText(QLatin1String("Qt.rgba"));
    d->qmlHslaBtn->setText(QLatin1String("Qt.hsla"));

    d->vec3Btn->setText(QLatin1String("vec3"));
    d->vec4Btn->setText(QLatin1String("vec4"));

    d->hexBtn->setText(QLatin1String("Hex"));

    d->rgbBtn->setCheckable(true);
    d->rgbAlphaBtn->setCheckable(true);
    d->rgbPercentBtn->setCheckable(true);
    d->hslBtn->setCheckable(true);
    d->hslAlphaBtn->setCheckable(true);
    d->hsvBtn->setCheckable(true);
    d->hsvAlphaBtn->setCheckable(true);
    d->qmlRgbaBtn->setCheckable(true);
    d->qmlHslaBtn->setCheckable(true);
    d->vec3Btn->setCheckable(true);
    d->vec4Btn->setCheckable(true);
    d->hexBtn->setCheckable(true);

    const int alphaAndPercentButtonWidth = 40;

    d->rgbAlphaBtn->setFixedWidth(alphaAndPercentButtonWidth);
    d->rgbPercentBtn->setFixedWidth(alphaAndPercentButtonWidth);
    d->hslAlphaBtn->setFixedWidth(alphaAndPercentButtonWidth);
    d->hsvAlphaBtn->setFixedWidth(alphaAndPercentButtonWidth);

    QHBoxLayout *rgbOptsLayout = new QHBoxLayout;
    rgbOptsLayout->setSpacing(0);
    rgbOptsLayout->addWidget(d->rgbAlphaBtn);
    rgbOptsLayout->addWidget(d->rgbPercentBtn);

    QGridLayout *formatsLayout = new QGridLayout;
    formatsLayout->addWidget(d->rgbBtn, 0, 0);
    formatsLayout->addLayout(rgbOptsLayout, 0, 1);

    formatsLayout->addWidget(d->hslBtn, 1, 0);
    formatsLayout->addWidget(d->hslAlphaBtn, 1, 1);

    formatsLayout->addWidget(d->hsvBtn, 2, 0);
    formatsLayout->addWidget(d->hsvAlphaBtn, 2, 1);

    formatsLayout->addWidget(d->qmlRgbaBtn, 3, 0);
    formatsLayout->addWidget(d->qmlHslaBtn, 3, 1);

    formatsLayout->addWidget(d->vec3Btn, 4, 0);
    formatsLayout->addWidget(d->vec4Btn, 4, 1);

    formatsLayout->addWidget(d->hexBtn, 5, 0);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(d->colorPicker);
    mainLayout->addWidget(d->opacitySlider);
    mainLayout->addWidget(d->hueSlider);
    mainLayout->addLayout(formatsLayout);

    //    layout->addWidget(d->colorFrame);

    // Color format selection logic
    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->addButton(d->rgbBtn);
    btnGroup->addButton(d->hslBtn);
    btnGroup->addButton(d->hsvBtn);
    btnGroup->addButton(d->qmlRgbaBtn);
    btnGroup->addButton(d->qmlHslaBtn);
    btnGroup->addButton(d->vec3Btn);
    btnGroup->addButton(d->vec4Btn);
    btnGroup->addButton(d->hexBtn);

    connect(btnGroup, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            this, &ColorDialog::onFormatButtonChecked);

    connect(d->rgbAlphaBtn, &QPushButton::toggled,
            [=](bool) {
        d->rgbBtn->click();
    });

    connect(d->rgbPercentBtn, &QPushButton::toggled,
            [=](bool) {
        d->rgbBtn->click();
    });

    connect(d->hslAlphaBtn, &QPushButton::toggled,
            [=](bool) {
        d->hslBtn->click();
    });

    connect(d->hsvAlphaBtn, &QPushButton::toggled,
            [=](bool) {
        d->hsvBtn->click();
    });

    // Color changes logic
    connect(d->colorPicker, &ColorPickerWidget::colorChanged,
            [=](const QColor &color) {
        d->updateColorWidgets(color, ColorDialogImpl::UpdateFromColorPicker);
    });

    connect(d->hueSlider, &HueSlider::valueChanged,
            [=](int hue) {
        QColor newColor = QColor::fromHsv(hue,
                                          d->outputColor.hsvSaturation(),
                                          d->outputColor.value(),
                                          d->opacitySlider->value());

        d->updateColorWidgets(newColor,
                              ColorDialogImpl::UpdateFromHueSlider);
    });

    connect(d->opacitySlider, &OpacitySlider::valueChanged,
            [=](int opacity) {
        QColor newColor = QColor::fromHsv(d->hueSlider->value(),
                                          d->outputColor.hsvSaturation(),
                                          d->outputColor.value(),
                                          opacity);

        d->updateColorWidgets(newColor,
                              ColorDialogImpl::UpdateFromOpacitySlider);
    });

    setColor(Qt::red);
}

ColorDialog::~ColorDialog()
{}

ColorFormat ColorDialog::outputColorFormat() const
{
    return d->outputColorFormat;
}

QColor ColorDialog::color() const
{
    return d->outputColor;
}

void ColorDialog::setColor(const QColor &color)
{
    if (d->outputColor != color) {
        d->updateColorWidgets(color, ColorDialogImpl::UpdateAll);

        emit colorChanged(color);
    }
}

int ColorDialog::hue() const
{
    return d->hueSlider->value();
}

void ColorDialog::setHue(int hue)
{
    Q_ASSERT(hue >= 0 && hue <= 359);

    if (d->hueSlider->value() != hue) {
        d->hueSlider->setValue(hue);

        emit hueChanged(hue);
    }
}

int ColorDialog::opacity() const
{
    return d->opacitySlider->value();
}

void ColorDialog::setOpacity(int opacity)
{
    Q_ASSERT(opacity >= 0 && opacity <= 255);

    if (d->opacitySlider->value() != opacity) {
        d->opacitySlider->setValue(opacity);

        emit opacityChanged(opacity);
    }
}

void ColorDialog::onFormatButtonChecked(QAbstractButton *checkedBtn)
{
    ColorFormat format;

    if (checkedBtn == d->rgbBtn) {
        bool useAlpha = d->rgbAlphaBtn->isChecked();
        bool usePercents = d->rgbPercentBtn->isChecked();

        if (useAlpha) {
            if (usePercents)
                format = ColorFormat::QCssRgbaAlphaPercentType;
            else
                format = ColorFormat::QCssRgbaAlphaFloatType;
        }
        else {
            if (usePercents)
                format = ColorFormat::QCssRgbPercentType;
            else
                format = ColorFormat::QCssRgbType;
        }
    }
    else if (checkedBtn == d->hslBtn) {
        bool useAlpha = d->hslAlphaBtn->isChecked();

        if (useAlpha)
            format = ColorFormat::CssHslaType;
        else
            format = ColorFormat::CssHslType;
    }
    else if (checkedBtn == d->hsvBtn) {
        bool useAlpha = d->hsvAlphaBtn->isChecked();

        if (useAlpha)
            format = ColorFormat::QssHsvaType;
        else
            format = ColorFormat::QssHsvType;
    }
    else if (checkedBtn == d->qmlRgbaBtn)
        format = ColorFormat::QmlRgbaType;
    else if (checkedBtn == d->qmlHslaBtn)
        format = ColorFormat::QmlHslaType;
    else if (checkedBtn == d->vec3Btn)
        format = ColorFormat::Vec3Type;
    else if (checkedBtn == d->vec4Btn)
        format = ColorFormat::Vec4Type;
    else if (checkedBtn == d->hexBtn)
        format = ColorFormat::HexType;

    d->outputColorFormat = format;
}

} // namespace Internal
} // namespace ColorPicker
