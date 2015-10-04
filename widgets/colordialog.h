#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QWidget>

class QFrame;

namespace ColorPicker {
namespace Internal {

class ColorPickerWidget;
class HueSlider;
class OpacitySlider;
class ColorDialogImpl;

class ColorDialog : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int hue READ hue WRITE setHue NOTIFY hueChanged)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

public:
    explicit ColorDialog(QWidget *parent = 0);
    ~ColorDialog();

    QColor color() const;
    int hue() const;
    int opacity() const;

public slots:
    void setColor(const QColor &color);
    void setHue(int hue);
    void setOpacity(int opacity);

signals:
    void colorChanged(const QColor &);
    void hueChanged(int);
    void opacityChanged(int);

private:
    QScopedPointer<ColorDialogImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORDIALOG_H
