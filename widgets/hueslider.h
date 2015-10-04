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

    QBrush gradientBrush() const override;
};

#endif // HUESLIDER_H

} // namespace Internal
} // namespace ColorPicker
