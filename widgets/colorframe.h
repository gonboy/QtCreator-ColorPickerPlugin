#ifndef COLORFRAME_H
#define COLORFRAME_H

#include <QFrame>

namespace ColorPicker {
namespace Internal {

class ColorFrame : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit ColorFrame(QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

signals:
    void colorChanged(QColor);

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;

private:
    QColor m_color;
    QBrush m_checkerboard;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORFRAME_H

