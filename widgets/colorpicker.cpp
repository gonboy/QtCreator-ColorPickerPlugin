#include "colorpicker.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorPickerWidgetImpl //////////////////////////

class ColorPickerWidgetImpl
{
public:
    ColorPickerWidgetImpl(ColorPickerWidget *qq) :
        q(qq),
        gradientImage(),
        color(QColor::Hsv),
        cursorPos(-1, -1)
    {}

    /* functions */

    // Many thanks to gbdivers > http://blog.developpez.com/gpu/?p=353
    void createGradientImage()
    {
        if (q->rect() != gradientImage.rect())
            gradientImage = QImage(q->size(), QImage::Format_RGB32);

        float h = color.hsvHueF();

        int qqWidth = q->width();
        int qqHeight = q->height();

        for (int s = 0; s < qqWidth; ++s) {
            for (int v = 0; v < qqHeight; ++v) {
                QColor color = QColor::fromHsvF(
                            h,
                            1.0 * s / (qqWidth - 1),
                            1.0 - (1.0 * v / (qqHeight - 1)));

                gradientImage.setPixel(s, v, color.rgb());
            }
        }
    }

    void updateCursorPos()
    {
        cursorPos = findPixel(color.rgb());
    }

    QColor colorUnderCursor(const QPoint &pos) const
    {
        return gradientImage.pixel(pos);
    }

    QPoint findPixel(const QColor &color) const
    {
        for (int i = 0; i < gradientImage.width(); ++i) {
            for (int j = 0; j < gradientImage.height(); ++j) {
                QColor pixel = QColor::fromRgb(gradientImage.pixel(i, j));

                if (pixel == color)
                    return QPoint(i, j);
            }
        }

        return QPoint(-1, -1);
    }

    void processMousePressAndMoveEvent(const QPoint &pos)
    {
        cursorPos = pos;

        if (!gradientImage.valid(cursorPos))
            return;

        color = colorUnderCursor(cursorPos);

        q->update();

        emit q->colorChanged(color);
    }

    /* variables */
    ColorPickerWidget *q;

    QImage gradientImage;
    QColor color;
    QPoint cursorPos;
};


////////////////////////// ColorPickerWidget //////////////////////////

ColorPickerWidget::ColorPickerWidget(QWidget *parent) :
    QWidget(parent),
    d(new ColorPickerWidgetImpl(this))
{
    setAttribute(Qt::WA_OpaquePaintEvent);
}

ColorPickerWidget::~ColorPickerWidget()
{}

QColor ColorPickerWidget::color() const
{
    return d->color;
}

QSize ColorPickerWidget::sizeHint() const
{
    return QSize(200, 200);
}

void ColorPickerWidget::setColor(const QColor &color)
{
    if (d->color != color) {
        d->color = color;

        d->createGradientImage();
        d->updateCursorPos();

        update();

        emit colorChanged(color);
    }
}

void ColorPickerWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(rect(), d->gradientImage);

    // Draw cursor circle
    {
        QPen pen(Qt::white);
        pen.setWidth(2);

        painter.setPen(pen);
        painter.drawEllipse(d->cursorPos, 7, 7);
    }
}

void ColorPickerWidget::resizeEvent(QResizeEvent *)
{
    d->createGradientImage();
    d->updateCursorPos();
}

void ColorPickerWidget::mousePressEvent(QMouseEvent *e)
{
    d->processMousePressAndMoveEvent(e->pos());
}

void ColorPickerWidget::mouseMoveEvent(QMouseEvent *e)
{
    d->processMousePressAndMoveEvent(e->pos());
}

} // namespace Internal
} // namespace ColorPicker
