#include "saturationslider.h"

#include <QPainter>

namespace ColorPicker {
namespace Internal {


////////////////////////// SaturationSlider //////////////////////////

SaturationSlider::SaturationSlider(QWidget *parent) :
    AdvancedSlider(parent),
    m_hue(0),
    m_gradient()
{
    setRange(0, 255);
}

void SaturationSlider::hsv(int *h, int *s, int *v) const
{
    *h = m_hue;
    *s = value();
    *v = 255;
}

void SaturationSlider::setHue(int h)
{
    if (m_hue != h) {
        m_hue = h;

        updateGradient();
        update();
    }
}

void SaturationSlider::resizeEvent(QResizeEvent *)
{
   updateGradient();
   update();
}

void SaturationSlider::drawBackground(QPainter *painter, const QRect &rect, int radius) const
{
    painter->setPen(QPen(Qt::black, 0.5));

    painter->setBrush(m_gradient);
    painter->drawRoundedRect(rect, radius, radius);
}

void SaturationSlider::drawHandleBackground(QPainter *painter, const QRect &rect, int radius) const
{
    painter->setBrush(QColor::fromHsv(m_hue, value(), 255));
    painter->drawRoundedRect(rect, radius,radius);
}

void SaturationSlider::updateGradient()
{
    m_gradient = QLinearGradient(QPoint(0.0, height()), QPoint(0.0, 0.0));

    m_gradient.setColorAt(0.0, QColor::fromHsv(m_hue, 0, 255));
    m_gradient.setColorAt(1.0, QColor::fromHsv(m_hue, 255, 255));
}

} // namespace Internal
} // namespace ColorPicker
