#ifndef OPACITYSLIDER_H
#define OPACITYSLIDER_H

#include <QSlider>

namespace ColorPicker {
namespace Internal {

class OpacitySliderImpl;

class OpacitySlider : public QSlider
{
    Q_OBJECT

public:
    explicit OpacitySlider(QWidget *parent = 0);
    ~OpacitySlider();

    void hsv(int *h, int *s, int *v) const;
    void setHsv(int h, int s, int v);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    QScopedPointer<OpacitySliderImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // OPACITYSLIDER_H
