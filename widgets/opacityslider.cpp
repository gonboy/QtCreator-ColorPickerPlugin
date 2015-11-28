#include "opacityslider.h"

// Qt includes
#include <QPainter>

// Plugin includes
#include "drawhelpers.h"

namespace ColorPicker {
namespace Internal {


////////////////////////// OpacitySliderImpl //////////////////////////

class OpacitySliderImpl
{
public:
    OpacitySliderImpl();

    /* functions */
    void updateCheckerboard(const QRect &rect);

    /* variables */
    int h, s, v;
    QBrush checkerboard;
};

OpacitySliderImpl::OpacitySliderImpl() :
    h(0),
    s(0),
    v(0),
    checkerboard()
{}

void OpacitySliderImpl::updateCheckerboard(const QRect &rect)
{
    checkerboard = opacityCheckerboard(rect, 3);
}


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
        update();
    }
}

void OpacitySlider::resizeEvent(QResizeEvent *)
{
    d->updateCheckerboard(rect());
}

void OpacitySlider::drawBackground(QPainter *painter, const QRect &rect, int radius) const
{
    painter->setBrush(d->checkerboard);
    painter->drawRoundedRect(rect, radius, radius);

    painter->setPen(QPen(Qt::black, 0.5));

    QLinearGradient gradient(QPoint(0.0, 0.0), QPoint(width(), height()));
    QColor gradientColor = QColor::fromHsv(d->h, d->s, d->v);

    gradientColor.setAlphaF(1.0);
    gradient.setColorAt(0.0, gradientColor);

    gradientColor.setAlphaF(0.0);
    gradient.setColorAt(1.0, gradientColor);

    painter->setBrush(gradient);
    painter->drawRoundedRect(rect, radius, radius);
}

void OpacitySlider::drawHandleBackground(QPainter *painter, const QRect &rect, int radius) const
{
    painter->setBrush(d->checkerboard);
    painter->drawRoundedRect(rect, radius, radius);

    painter->setBrush(QColor::fromHsv(d->h, d->s, d->v, value()));
    painter->drawRoundedRect(rect, radius, radius);
}

} // namespace Internal
} // namespace ColorPicker
