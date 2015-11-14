#include "advancedslider.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionSlider>

AdvancedSlider::AdvancedSlider(QWidget *parent) :
    QSlider(parent),
    m_backgroundBrush(),
    m_gradientBrush()
{}

void AdvancedSlider::setValueAtomic(int newValue)
{
    const QSignalBlocker blocker(this);

    setValue(newValue);
}

QBrush AdvancedSlider::backgroundBrush() const
{
    return Qt::NoBrush;
}

QBrush AdvancedSlider::gradientBrush() const
{
    return Qt::NoBrush;
}

void AdvancedSlider::updateBrushes()
{
    m_backgroundBrush = backgroundBrush();
    m_gradientBrush = gradientBrush();
}

void AdvancedSlider::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    painter.save();

    // Draw background
    QRect myRect = rect();
    const int rectRadius = 7;

    painter.setBrush(m_backgroundBrush);
    painter.drawRoundedRect(myRect, rectRadius, rectRadius);

    painter.setPen(QPen(Qt::black, 0.5));

    painter.setBrush(m_gradientBrush);
    painter.drawRoundedRect(myRect, rectRadius, rectRadius);

    painter.restore();

    // Draw handle
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle);
    handleRect.setWidth(width());

    QPen pen(Qt::white);
    pen.setWidth(4);

    painter.setPen(pen);
    painter.drawRoundedRect(handleRect, rectRadius, rectRadius);
}

void AdvancedSlider::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    updateBrushes();
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
