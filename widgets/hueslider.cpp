#include "hueslider.h"

#include <QPainter>
#include <QStyleOptionSlider>

namespace ColorPicker {
namespace Internal {


////////////////////////// HueSliderImpl //////////////////////////

class HueSliderImpl
{
public:
    HueSliderImpl(HueSlider *qq) :
        q_ptr(qq)
    {}

    /* functions */
    void createGradientImage()
    {
        QLinearGradient gradient(QPoint(0.0, q_ptr->height()), QPoint(0.0, 0.0));

        qreal nextGradientStop = 0;

        for (int nextHue = 0; nextHue <= 360; nextHue += 60)
        {
            if (nextHue == 360)
                nextHue = 359;

            gradient.setColorAt(nextGradientStop, QColor::fromHsv(nextHue, 255, 255));

            nextGradientStop += 1.0 / 6;
        }

        QPixmap pix(q_ptr->size());

        QPainter painter(&pix);
        painter.setPen(QPen(Qt::NoPen));
        painter.setBrush(gradient);
        painter.drawRect(q_ptr->rect());

        gradientImage = pix.toImage();
    }

    /* variables */
    HueSlider *q_ptr;
    QImage gradientImage;
};


////////////////////////// HueSlider //////////////////////////

HueSlider::HueSlider(QWidget *parent) :
    QSlider(parent),
    d(new HueSliderImpl(this))
{
    setRange(0, 359);
}

HueSlider::~HueSlider()
{}

void HueSlider::paintEvent(QPaintEvent *)
{
    if (rect() != d->gradientImage.rect())
        d->gradientImage = QImage(size(), QImage::Format_RGB32);

    QPainter painter(this);
    painter.drawImage(rect(), d->gradientImage);

    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle);
    handleRect.setTopLeft(QPoint(0, handleRect.topLeft().y()));
    handleRect.setWidth(width());

    QPen pen(Qt::white);
    pen.setWidth(4);

    painter.setPen(pen);
    painter.drawRect(handleRect);

}

void HueSlider::resizeEvent(QResizeEvent *)
{
    d->createGradientImage();
}

} // namespace Internal
} // namespace ColorPicker
