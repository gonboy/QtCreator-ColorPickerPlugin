#ifndef VALUESLIDER_H
#define VALUESLIDER_H

#include "advancedslider.h"

namespace ColorPicker {
namespace Internal {

class ValueSlider : public AdvancedSlider
{
    Q_OBJECT

public:
    explicit ValueSlider(QWidget *parent = 0);

    void hsv(int *h, int *s, int *v) const;
    void setHue(int h);

protected:
    void resizeEvent(QResizeEvent *) override;

    void drawBackground(QPainter *painter, const QRect &rect, int radius) const override;
    void drawHandleBackground(QPainter *painter, const QRect &rect, int radius) const override;

private:
    void updateGradient();

private:
    int m_hue;
    QLinearGradient m_gradient;
};

} // namespace Internal
} // namespace ColorPicker

#endif // VALUESLIDER_H
