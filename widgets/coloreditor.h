#ifndef COLOREDITOR_H
#define COLOREDITOR_H

#include <QFrame>

#include "../colorutilities.h"

class QAbstractButton;

namespace ColorPicker {
namespace Internal {

class ColorEditorImpl;
class ColorPickerWidget;
class HueSlider;
class OpacitySlider;

class ColorEditor : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(ColorFormat outputFormat READ outputFormat WRITE setOutputFormat NOTIFY outputFormatChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int hue READ hue WRITE setHue NOTIFY hueChanged)
    Q_PROPERTY(int opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

public:
    explicit ColorEditor(QWidget *parent = 0);
    ~ColorEditor();

    ColorCategory colorCategory() const;
    void setColorCategory(ColorCategory category);

    ColorFormatSet availableFormats() const;

    ColorFormat outputFormat() const;

    QColor color() const;
    int hue() const;
    int opacity() const;

public slots:
    void setOutputFormat(ColorFormat format);

    void setColor(const QColor &color);
    void setHue(int hue);
    void setOpacity(int opacity);

signals:
    void outputFormatChanged(ColorFormat);
    void colorChanged(const QColor &);
    void hueChanged(int);
    void opacityChanged(int);

protected:
    void paintEvent(QPaintEvent *) override;

private slots:
    void onFormatButtonChecked(QAbstractButton *checkedBtn);

private:
    QScopedPointer<ColorEditorImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLOREDITOR_H
