#ifndef HUESLIDER_H
#define HUESLIDER_H

#include "advancedslider.h"

namespace ColorPicker {
namespace Internal {

class HueSlider : public AdvancedSlider
{
    Q_OBJECT

public:
    explicit HueSlider(QWidget *parent = 0);
    ~HueSlider();

protected:
    void resizeEvent(QResizeEvent *) override;

    void drawBackground(QPainter *painter, const QRect &rect, int radius) const override;
    void drawHandleBackground(QPainter *painter, const QRect &rect, int radius) const override;

private:
    QLinearGradient m_gradient;
};

#endif // HUESLIDER_H

} // namespace Internal
} // namespace ColorPicker
