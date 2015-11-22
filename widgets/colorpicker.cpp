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
    ColorPickerWidgetImpl(ColorPickerWidget *qq);

    /* functions */
    void createGradientImage(float hueF);

    QColor positionToColor(const QPoint &pos) const;
    QPoint colorToPosition(const QColor &color) const;

    QPoint clampPos(const QPoint &pos, const QRect &rect) const;

    void processMouseEvent(QMouseEvent *e);
    void updateInternalColor(const QColor &color);

    /* variables */
    ColorPickerWidget *q;

    QImage gradientImage;
    QColor color;
    QPoint cursorPos;
};

ColorPickerWidgetImpl::ColorPickerWidgetImpl(ColorPickerWidget *qq) :
    q(qq),
    gradientImage(),
    color(QColor::Hsv),
    cursorPos(-1, -1)
{}

// Many thanks to gbdivers > http://blog.developpez.com/gpu/?p=353
void ColorPickerWidgetImpl::createGradientImage(float hueF)
{
    if (q->rect() != gradientImage.rect())
        gradientImage = QImage(q->size(), QImage::Format_RGB32);

    int qWidth = q->width();
    int qHeight = q->height();

    for (int s = 0; s < qWidth; ++s) {
        for (int v = 0; v < qHeight; ++v) {
            QColor color = QColor::fromHsvF(
                        hueF,
                        1.0 * s / (qWidth - 1),
                        1.0 - (1.0 * v / (qHeight - 1)));

            gradientImage.setPixel(s, v, color.rgb());
        }
    }
}

QColor ColorPickerWidgetImpl::positionToColor(const QPoint &pos) const
{
    float s = 1.0 * static_cast<float>(pos.x()) / (q->width() - 1);
    float v = 1.0 - (1.0 * static_cast<float>(pos.y()) / (q->height() - 1));

    return QColor::fromHsvF(color.hueF(), s, v);
}

QPoint ColorPickerWidgetImpl::colorToPosition(const QColor &color) const
{
    int x = color.saturationF() * (q->width() - 1);
    int y = (1 - color.valueF()) * (q->height() - 1);

    return QPoint(x, y);
}

QPoint ColorPickerWidgetImpl::clampPos(const QPoint &pos, const QRect &rect) const
{
    int x = pos.x();
    int rLeft = rect.left();
    int rRight = rect.right();

    if (x < rLeft)
        x = rLeft;
    else if (x > rRight)
        x = rRight;

    int y = pos.y();
    int rTop = rect.top();
    int rBottom = rect.bottom();

    if (y < rTop)
        y = rTop;
    else if (y > rBottom)
        y = rBottom;

    return QPoint(x, y);
}

void ColorPickerWidgetImpl::processMouseEvent(QMouseEvent *e)
{
    QPoint pos = e->pos();
    QRect qRect = q->rect();

    if (!qRect.contains(pos))
        pos = clampPos(pos, qRect);

    cursorPos = pos;

    QColor posColor = positionToColor(pos);
    updateInternalColor(posColor);

    e->accept();
}

void ColorPickerWidgetImpl::updateInternalColor(const QColor &c)
{
    float newHue = c.hueF();

    if (color.hueF() != newHue)
        createGradientImage(newHue);

    color = c;

    q->update();
    emit q->colorChanged(c);
}


////////////////////////// ColorPickerWidget //////////////////////////

ColorPickerWidget::ColorPickerWidget(QWidget *parent) :
    QWidget(parent),
    d(new ColorPickerWidgetImpl(this))
{
    setFocusPolicy(Qt::StrongFocus);
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
        d->cursorPos = d->colorToPosition(color);

        d->updateInternalColor(color);
    }
}

void ColorPickerWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
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
    d->createGradientImage(d->color.hueF());
}

void ColorPickerWidget::mousePressEvent(QMouseEvent *e)
{
    d->processMouseEvent(e);
}

void ColorPickerWidget::mouseMoveEvent(QMouseEvent *e)
{
    d->processMouseEvent(e);
}

void ColorPickerWidget::keyPressEvent(QKeyEvent *e)
{
    int h, s ,v;
    d->color.getHsv(&h, &s, &v);

    switch (e->key()) {
    case Qt::Key_Left:
        if (s > 0)
            --s;
        break;
    case Qt::Key_Right:
        if (s < 255)
            ++s;
        break;
    case Qt::Key_Up:
        if (v < 255)
            ++v;
        break;
    case Qt::Key_Down:
        if (v > 0)
            --v;
        break;
    default:
        break;
    }

    QColor c = QColor::fromHsv(h, s, v);
    setColor(c);
}

} // namespace Internal
} // namespace ColorPicker
