#ifndef COLORPICKERSETTINGSWIDGET_H
#define COLORPICKERSETTINGSWIDGET_H

#include <QWidget>

class QCheckBox;

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
    QCheckBox *m_editorSensitiveCheckBox;
    QCheckBox *m_insertOnChangeCheckBox;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKERSETTINGSWIDGET_H
