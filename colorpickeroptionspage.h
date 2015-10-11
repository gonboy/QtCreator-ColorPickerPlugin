#ifndef COLORPICKEROPTIONSPAGE_H
#define COLORPICKEROPTIONSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>

#include <QPointer>

namespace ColorPicker {
namespace Internal {

class ColorPickerOptionsPageImpl;
class ColorPickerSettingsWidget;
class GeneralSettings;

class ColorPickerOptionsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    explicit ColorPickerOptionsPage(QObject *parent = 0);
    ~ColorPickerOptionsPage();

    const GeneralSettings &generalSettings() const;

    QWidget *widget() override;
    void apply() override;
    void finish() override;

signals:
    void generalSettingsChanged(const GeneralSettings &);

private:
    QScopedPointer<ColorPickerOptionsPageImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORPICKEROPTIONSPAGE_H
