#ifndef ADVANDEDSLIDER_H
#define ADVANDEDSLIDER_H

#include <QSlider>

namespace ColorPicker {
namespace Internal {

class AdvancedSlider : public QSlider
{
    Q_OBJECT

public:
    AdvancedSlider(QWidget *parent = 0);

    void setValueAtomic(int newValue);

protected:
    void paintEvent(QPaintEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;

    virtual void drawBackground(QPainter *painter, const QRect &rect, int radius) const;
    virtual void drawHandleBackground(QPainter *painter, const QRect &rect, int radius) const;
};

} // namespace Internal
} // namespace ColorPicker

#endif // ADVANDEDSLIDER_H
