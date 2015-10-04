#ifndef OPACITYSLIDER_H
#define OPACITYSLIDER_H

#include "advancedslider.h"

namespace ColorPicker {
namespace Internal {

class OpacitySliderImpl;

class OpacitySlider : public AdvancedSlider
{
    Q_OBJECT

public:
    explicit OpacitySlider(QWidget *parent = 0);
    ~OpacitySlider();

    void hsv(int *h, int *s, int *v) const;
    void setHsv(int h, int s, int v);

    QBrush backgroundBrush() const override;
    QBrush gradientBrush() const override;

private:
    QScopedPointer<OpacitySliderImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // OPACITYSLIDER_H
