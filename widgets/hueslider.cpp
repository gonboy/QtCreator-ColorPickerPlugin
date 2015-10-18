#include "hueslider.h"

#include <QPainter>

namespace ColorPicker {
namespace Internal {


////////////////////////// HueSlider //////////////////////////

HueSlider::HueSlider(QWidget *parent) :
    AdvancedSlider(parent)
{
    setRange(0, 359);
}

HueSlider::~HueSlider()
{}


QBrush HueSlider::gradientBrush() const
{
    QLinearGradient gradient(QPoint(0.0, height()), QPoint(0.0, 0.0));

    qreal nextGradientStop = 0;

    for (int nextHue = 0; nextHue <= 360; nextHue += 60)
    {
        if (nextHue == 360)
            nextHue = 359;

        gradient.setColorAt(nextGradientStop, QColor::fromHsv(nextHue, 255, 255));

        nextGradientStop += 1.0 / 6;
    }

    return gradient;
}

} // namespace Internal
} // namespace ColorPicker
