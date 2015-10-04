#include "colordialog.h"

#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>

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
        outputColor(QColor::Hsv),
        colorPicker(new ColorPickerWidget(q_ptr)),
        hueSlider(new HueSlider(q_ptr)),
        opacitySlider(new OpacitySlider(q_ptr))/*,*/
      //        d->colorFrame(new QFrame(q_ptr))
    {}

    /* functions */
    void blockSignals(bool block)
    {
        colorPicker->blockSignals(block);
        hueSlider->blockSignals(block);
        opacitySlider->blockSignals(block);
    }

    void updateWidgets(const QColor &color, UpdateReasons whichUpdate)
    {
        blockSignals(true);

        if (whichUpdate & ColorDialogImpl::UpdateFromColorPicker)
            opacitySlider->setHsv(color.hsvHue(), color.hsvSaturation(), color.value());

        if (whichUpdate & ColorDialogImpl::UpdateFromHueSlider) {
            colorPicker->setColor(color);
            opacitySlider->setHsv(color.hsvHue(), color.hsvSaturation(), color.value());
        }

        if (whichUpdate & ColorDialogImpl::UpdateFromOpacitySlider) {

        }

        if (whichUpdate & ColorDialogImpl::UpdateProgrammatically) {
            hueSlider->setValue(color.hsvHue());
            opacitySlider->setValue(color.alpha());
        }

        outputColor = color;

        blockSignals(false);
    }

    /* variables */
    ColorDialog *q_ptr;

    QColor outputColor;

    ColorPickerWidget *colorPicker;
    HueSlider *hueSlider;
    OpacitySlider *opacitySlider;
    //    QFrame *d->colorFrame;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ColorDialogImpl::UpdateReasons)


////////////////////////// ColorDialog //////////////////////////

ColorDialog::ColorDialog(QWidget *parent) :
    QWidget(parent),
    d(new ColorDialogImpl(this))
{
    //    d->colorFrame->setFixedSize(50, 50);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(d->colorPicker);
    layout->addWidget(d->opacitySlider);
    layout->addWidget(d->hueSlider);
    //    layout->addWidget(d->colorFrame);

    connect(d->colorPicker, &ColorPickerWidget::colorChanged,
            [=](const QColor &color) {
        d->updateWidgets(color, ColorDialogImpl::UpdateFromColorPicker);
    });

    connect(d->hueSlider, &HueSlider::valueChanged,
            [=](int hue) {
        QColor newColor = QColor::fromHsv(hue,
                                          d->outputColor.hsvSaturation(),
                                          d->outputColor.value(),
                                          d->opacitySlider->value());

        d->updateWidgets(newColor,
                         ColorDialogImpl::UpdateFromHueSlider);
    });

    connect(d->opacitySlider, &OpacitySlider::valueChanged,
            [=](int opacity) {
        QColor newColor = QColor::fromHsv(d->hueSlider->value(),
                                          d->outputColor.hsvSaturation(),
                                          d->outputColor.value(),
                                          opacity);

        d->updateWidgets(newColor,
                         ColorDialogImpl::UpdateFromOpacitySlider);
    });

    setColor(Qt::blue);
}

ColorDialog::~ColorDialog()
{}

QColor ColorDialog::color() const
{
    return d->outputColor;
}

void ColorDialog::setColor(const QColor &color)
{
    if (d->outputColor != color) {
        d->updateWidgets(color, ColorDialogImpl::UpdateAll);

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

} // namespace Internal
} // namespace ColorPicker
