#include "colordialog.h"

#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QTabWidget>

#include "colorpicker.h"
#include "hueslider.h"
#include "opacityslider.h"

#include "../langcontexts/csslangcontext.h"
#include "../langcontexts/qsslangcontext.h"

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
        langContexts(),
        outputColor(QColor::Hsv),
        langTabs(new QTabWidget(q_ptr)),
        colorPicker(new ColorPickerWidget(q_ptr)),
        hueSlider(new HueSlider(q_ptr)),
        opacitySlider(new OpacitySlider(q_ptr))/*,*/
      //        d->colorFrame(new QFrame(q_ptr))
    {}

    /* functions */
    void updateWidgets(const QColor &color, UpdateReasons whichUpdate)
    {
        if (whichUpdate & ColorDialogImpl::UpdateFromColorPicker)
            opacitySlider->setHsv(color.hsvHue(), color.hsvSaturation(), color.value());

        if (whichUpdate & ColorDialogImpl::UpdateFromHueSlider) {
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
    }

    void addLangContext(ILangContext *lc)
    {
        if (!langContexts.contains(lc))
            langContexts << lc;

        langTabs->addTab(lc, lc->displayName());

        QObject::connect(lc, &ILangContext::formatChoosed,
                         q_ptr, &ColorDialog::onColorFormatChoosed);
    }

    /* variables */
    ColorDialog *q_ptr;

    ColorFormat outputColorFormat;
    QList<ILangContext *> langContexts;
    QColor outputColor;

    QTabWidget *langTabs;
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

    // Build UI
    d->addLangContext(new QssLangContext);
    d->addLangContext(new CssLangContext);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(d->colorPicker);
    layout->addWidget(d->opacitySlider);
    layout->addWidget(d->hueSlider);
    layout->addWidget(d->langTabs);
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

void ColorDialog::onColorFormatChoosed(ColorFormat colorFormat)
{
    d->outputColorFormat = colorFormat;

    ILangContext *senderContext = qobject_cast<ILangContext *>(sender());
    Q_ASSERT(senderContext);

    for (ILangContext *lc : d->langContexts) {
        if (lc != senderContext)
            lc->uncheck();
    }
}

} // namespace Internal
} // namespace ColorPicker
