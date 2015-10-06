#ifndef COLORPICKEROPTIONSPAGE_H
#define COLORPICKEROPTIONSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>

#include <QPointer>

namespace ColorPicker {
namespace Internal {

class ColorPickerSettingsWidget;

class ColorPickerOptionsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    explicit ColorPickerOptionsPage(QObject *parent = 0);

    QWidget *widget() override;
    void apply() override;
    void finish() override;

private:
    QPointer<ColorPickerSettingsWidget> m_widget;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKEROPTIONSPAGE_H
