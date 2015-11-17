#include "advancedslider.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionSlider>

namespace ColorPicker {
namespace Internal {

AdvancedSlider::AdvancedSlider(QWidget *parent) :
    QSlider(parent)
{}

void AdvancedSlider::setValueAtomic(int newValue)
{
    const QSignalBlocker blocker(this);

    setValue(newValue);
}

void AdvancedSlider::drawBackground(QPainter *painter, const QRect &rect, int radius) const
{
    Q_UNUSED(painter);
    Q_UNUSED(rect);
    Q_UNUSED(radius);
}

void AdvancedSlider::drawHandleBackground(QPainter *painter, const QRect &rect, int radius) const
{
    Q_UNUSED(painter);
    Q_UNUSED(rect);
    Q_UNUSED(radius);
}

void AdvancedSlider::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    painter.save();

    // Draw background
    QRect myRect = rect().adjusted(3, 0, -3, 0);
    const int rectRadius = 3;

    drawBackground(&painter, myRect, rectRadius);

    painter.restore();

    // Draw handle
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle);
    handleRect.adjust(1, 1, -1, -1);
    const int handleRadius = 7;

    QPen pen(Qt::white);
    pen.setWidth(2);

    painter.setPen(pen);
    drawHandleBackground(&painter, handleRect, handleRadius);
}

void AdvancedSlider::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (orientation() == Qt::Vertical)
            setValue(minimum() + ((maximum()-minimum()) * (height()-e->y())) / height() ) ;
        else
            setValue(minimum() + ((maximum()-minimum()) * e->x()) / width() ) ;

        e->accept();
    }

    QSlider::mousePressEvent(e);
}

} // namespace Internal
} // namespace ColorPicker
