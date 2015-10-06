#ifndef COLORPICKERSETTINGSWIDGET_H
#define COLORPICKERSETTINGSWIDGET_H

#include <QWidget>

namespace ColorPicker {
namespace Internal {

class ColorPickerSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPickerSettingsWidget(QWidget *parent = 0);
    ~ColorPickerSettingsWidget();

signals:

public slots:
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERSETTINGSWIDGET_H
