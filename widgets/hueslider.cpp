#include "hueslider.h"

#include <QPainter>

namespace ColorPicker {
namespace Internal {


////////////////////////// HueSlider //////////////////////////

HueSlider::HueSlider(QWidget *parent) :
    AdvancedSlider(parent),
    m_gradient()
{
    setRange(0, 359);
}

HueSlider::~HueSlider()
{}

void HueSlider::resizeEvent(QResizeEvent *)
{
    // Update the hue gradient
    m_gradient = QLinearGradient(QPoint(0.0, height()), QPoint(0.0, 0.0));

    qreal nextGradientStop = 0;

    for (int nextHue = 0; nextHue <= 360; nextHue += 60)
    {
        if (nextHue == 360)
            nextHue = 359;

        m_gradient.setColorAt(nextGradientStop, QColor::fromHsv(nextHue, 255, 255));

        nextGradientStop += 1.0 / 6;
    }
}

void HueSlider::drawBackground(QPainter *painter, const QRect &rect, int radius) const
{
    painter->setPen(QPen(Qt::black, 0.5));

    painter->setBrush(m_gradient);
    painter->drawRoundedRect(rect, radius, radius);
}

void HueSlider::drawHandleBackground(QPainter *painter, const QRect &rect, int radius) const
{
    painter->setBrush(QColor::fromHsv(value(), 255, 255));
    painter->drawRoundedRect(rect, radius,radius);
}

} // namespace Internal
} // namespace ColorPicker
