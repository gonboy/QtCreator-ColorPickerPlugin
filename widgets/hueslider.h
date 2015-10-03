#ifndef HUESLIDER_H
#define HUESLIDER_H

#include <QSlider>

namespace ColorPicker {
namespace Internal {

class HueSliderImpl;

class HueSlider : public QSlider
{
    Q_OBJECT

public:
    explicit HueSlider(QWidget *parent = 0);
    ~HueSlider();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

private:
    QScopedPointer<HueSliderImpl> d;
};

#endif // HUESLIDER_H

} // namespace Internal
} // namespace ColorPicker
