#ifndef COLORPICKERSETTINGSWIDGET_H
#define COLORPICKERSETTINGSWIDGET_H

#include <QWidget>

namespace ColorPicker {
namespace Internal {

class GeneralSettings;

class ColorPickerSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorPickerSettingsWidget(QWidget *parent = 0);
    ~ColorPickerSettingsWidget();

    void settingsFromUI(GeneralSettings *settings);
    void settingsToUI(const GeneralSettings settings);

private:
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERSETTINGSWIDGET_H
