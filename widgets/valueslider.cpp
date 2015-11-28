#include "valueslider.h"

#include <QPainter>

namespace ColorPicker {
namespace Internal {


////////////////////////// ValueSlider //////////////////////////

ValueSlider::ValueSlider(QWidget *parent) :
    AdvancedSlider(parent),
    m_hue(0),
    m_gradient()
{
    setRange(0, 255);
}

void ValueSlider::hsv(int *h, int *s, int *v) const
{
    *h = m_hue;
    *s = 255;
    *v = value();
}

void ValueSlider::setHue(int h)
{
    if (m_hue != h) {
        m_hue = h;

        updateGradient();
        update();
    }
}

void ValueSlider::resizeEvent(QResizeEvent *)
{
    updateGradient();
    update();
}

void ValueSlider::drawBackground(QPainter *painter, const QRect &rect, int radius) const
{
    painter->setPen(QPen(Qt::black, 0.5));

    painter->setBrush(m_gradient);
    painter->drawRoundedRect(rect, radius, radius);
}

void ValueSlider::drawHandleBackground(QPainter *painter, const QRect &rect, int radius) const
{
    painter->setBrush(QColor::fromHsv(m_hue, 255, value()));
    painter->drawRoundedRect(rect, radius,radius);
}

void ValueSlider::updateGradient()
{
    m_gradient = QLinearGradient(QPoint(0.0, height()), QPoint(0.0, 0.0));

    m_gradient.setColorAt(0.0, QColor::fromHsv(m_hue, 255, 0));
    m_gradient.setColorAt(1.0, QColor::fromHsv(m_hue, 255, 255));
}

} // namespace Internal
} // namespace ColorPicker
