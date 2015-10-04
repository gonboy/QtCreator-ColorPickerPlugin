#include "opacityslider.h"

#include <QDebug>
#include <QPainter>

namespace ColorPicker {
namespace Internal {


////////////////////////// OpacitySliderImpl //////////////////////////

class OpacitySliderImpl
{
public:
    OpacitySliderImpl() :
        h(0),
        s(0),
        v(0)
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

    /* variables */
    int h, s, v;
};


//////////////////////////// OpacitySlider /////////////////////////////

OpacitySlider::OpacitySlider(QWidget *parent)
    : AdvancedSlider(parent),
      d(new OpacitySliderImpl)
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
        updateBrushes();

        update();
    }
}

QBrush OpacitySlider::backgroundBrush() const
{
    return d->opacityCheckerboard(rect());
}

QBrush OpacitySlider::gradientBrush() const
{
    QLinearGradient colorGradient(QPoint(0.0, 0.0), QPoint(width(), height()));
    QColor gradientColor = QColor::fromHsv(d->h, d->s, d->v);

    gradientColor.setAlphaF(1.0);
    colorGradient.setColorAt(0.0, gradientColor);

    gradientColor.setAlphaF(0.0);
    colorGradient.setColorAt(1.0, gradientColor);

    return colorGradient;
}

} // namespace Internal
} // namespace ColorPicker
