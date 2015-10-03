#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QWidget>

namespace ColorPicker {
namespace Internal {

class ColorPickerWidgetImpl;

class ColorPickerWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit ColorPickerWidget(QWidget *parent = 0);
    ~ColorPickerWidget();

    QColor color() const;

    QSize sizeHint() const;

signals:
    void colorChanged(QColor);

public slots:
    void setColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    QScopedPointer<ColorPickerWidgetImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERWIDGET_H
