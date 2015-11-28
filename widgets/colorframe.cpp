#include "colorframe.h"

// Qt includes
#include <QPainter>
#include <QPushButton>
#include <QResizeEvent>

// Plugin includes
#include "drawhelpers.h"

namespace ColorPicker {
namespace Internal {

ColorFrame::ColorFrame(QWidget *parent) :
    QFrame(parent),
    m_color(QColor::Hsv),
    m_checkerboard()
{}

QColor ColorFrame::color() const
{
    return m_color;
}

void ColorFrame::setColor(const QColor &color)
{
    if (m_color != color) {
        m_color = color;

        update();

        emit colorChanged(color);
    }
}

void ColorFrame::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    QRect myRect = rect();

    painter.setBrush(m_checkerboard);
    painter.drawRect(myRect);

    painter.setPen(QPen(Qt::black, 0.5));

    painter.setBrush(m_color);
    painter.drawRect(myRect);
}

void ColorFrame::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);

    if (e->size().isEmpty())
        return;

    m_checkerboard = opacityCheckerboard(rect(), 5);
}

} // namespace Internal
} // namespace ColorPicker
