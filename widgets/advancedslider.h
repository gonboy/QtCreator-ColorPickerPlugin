#ifndef ADVANDEDSLIDER_H
#define ADVANDEDSLIDER_H

#include <QSlider>

class AdvancedSlider : public QSlider
{
    Q_OBJECT

public:
    AdvancedSlider(QWidget *parent = 0);

    void setValueAtomic(int newValue);

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;

    virtual QBrush backgroundBrush() const;
    virtual QBrush gradientBrush() const;

    void updateBrushes();

private:
    QBrush m_backgroundBrush;
    QBrush m_gradientBrush;
};

#endif // ADVANDEDSLIDER_H
