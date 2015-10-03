#include "opacityslider.h"

#include <QDebug>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionSlider>

namespace ColorPicker {
namespace Internal {


////////////////////////// OpacitySliderImpl //////////////////////////

class OpacitySliderImpl
{
public:
    OpacitySliderImpl(OpacitySlider *qq) :
        q_ptr(qq),
        h(0),
        s(0),
        v(0),
        gradientImage()
    {}

    /* functions */
    QImage opacityCheckerboard(const QRect &rect, int xSquareCount = 3) const
    {
        QPixmap pix(rect.size());
        pix.fill();

        QPainter painter(&pix);
        painter.setPen(QPen(Qt::NoPen));
        painter.setBrush(Qt::gray);

        int squareSide = rect.width() / xSquareCount;
        int ySquareCount = rect.height() / squareSide;

        QSize squareSize(squareSide, squareSide);
        QPoint currentTopLeft;

        for (int i = 0; i < xSquareCount; ++i)
        {
            bool inverseBrushesOrder = (i % 2) == 0;

            for (int j = 0; j < ySquareCount; ++j)
            {
                if (j % 2 == 0)
                {
                    if (inverseBrushesOrder)
                        painter.drawRect(QRect(currentTopLeft, squareSize));
                }
                else
                {
                    if (!inverseBrushesOrder)
                        painter.drawRect(QRect(currentTopLeft, squareSize));
                }

                currentTopLeft.ry() += squareSide;
            }

            currentTopLeft.rx() += squareSide;
            currentTopLeft.ry() = 0;
        }

        return pix.toImage();
    }

    void createGradientImage()
    {
        QPixmap pix(q_ptr->size());

        QPainter painter(&pix);
        painter.setPen(QPen(Qt::NoPen));

        QRect qqRect = q_ptr->rect();

        // draw opacity pattern
        painter.setBrush(opacityCheckerboard(qqRect));
        painter.drawRect(qqRect);

        // draw color gradient
        QLinearGradient colorGradient(QPoint(0.0, 0.0), QPoint(q_ptr->width(), q_ptr->height()));
        QColor gradientColor = QColor::fromHsv(h, s, v);

        gradientColor.setAlphaF(1.0);
        colorGradient.setColorAt(0.0, gradientColor);

        gradientColor.setAlphaF(0.0);
        colorGradient.setColorAt(1.0, gradientColor);

        painter.setBrush(colorGradient);
        painter.drawRect(qqRect);

        gradientImage = pix.toImage();
    }

    /* variables */
    OpacitySlider *q_ptr;

    int h, s, v;
    QImage gradientImage;
};


//////////////////////////// OpacitySlider /////////////////////////////

OpacitySlider::OpacitySlider(QWidget *parent)
    : QSlider(parent),
      d(new OpacitySliderImpl(this))
{
    setRange(0, 255);
    setValue(255);
}

OpacitySlider::~OpacitySlider()
{}

void OpacitySlider::hsv(int *h, int *s, int *v) const
{
    *h = d->h;
    *s = d->s;
    *v = d->v;
}

void OpacitySlider::setHsv(int h, int s, int v)
{
    bool updateImage = false;

    if (d->h != h) {
        d->h = h;
        updateImage = true;
    }

    if (d->s != s) {
        d->s = s;
        updateImage = true;
    }

    if (d->v != v) {
        d->v = v;
        updateImage = true;
    }

    if (updateImage) {
        d->createGradientImage();

        update();
    }
}

void OpacitySlider::paintEvent(QPaintEvent *)
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

void OpacitySlider::resizeEvent(QResizeEvent *)
{
    d->createGradientImage();
}

} // namespace Internal
} // namespace ColorPicker
