#include "colorpickeroptionspage.h"

// Qt includes
#include <QCoreApplication>
#include <QDebug>

// QtCreator includes
#include <coreplugin/icore.h>

// Plugin includes
#include "colorpickerconstants.h"
#include "generalsettings.h"
#include "widgets/colorpickersettingswidget.h"

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorPickerOptionsPageImpl //////////////////////////

class ColorPickerOptionsPageImpl
{
public:
    ColorPickerOptionsPageImpl() :
        settingsPrefix(QLatin1String(Constants::COLORPICKER_SETTINGS_PREFIX)),
        generalSettings()
    {}

    ~ColorPickerOptionsPageImpl()
    {}

    /* functions */
    void init()
    {
        const QSettings *s = Core::ICore::settings();

        generalSettings.fromSettings(settingsPrefix, s);
    }

    /* variables */
    QString settingsPrefix;
    GeneralSettings generalSettings;
    QPointer<ColorPickerSettingsWidget> widget;
};


////////////////////////// ColorPickerOptionsPage //////////////////////////

ColorPickerOptionsPage::ColorPickerOptionsPage(QObject *parent) :
    Core::IOptionsPage(parent),
    d(new ColorPickerOptionsPageImpl)
{
    setId(Constants::COLORPICKER_SETTINGS_ID);
    setDisplayName(tr(Constants::COLORPICKER_SETTINGS_DISPLAY_NAME));
    setCategory(Constants::COLORPICKER_SETTINGS_CATEGORY);
    setDisplayCategory(QCoreApplication::translate("ColorPicker",
                                                   Constants::COLORPICKER_SETTINGS_TR_CATEGORY));
    setCategoryIcon(QLatin1String(Constants::COLORPICKER_SETTINGS_CATEGORY_ICON));

    d->init();
}

ColorPickerOptionsPage::~ColorPickerOptionsPage()
{}

const GeneralSettings &ColorPickerOptionsPage::generalSettings() const
{
    return d->generalSettings;
}

QWidget *ColorPickerOptionsPage::widget()
{
    if (!d->widget)
        d->widget = new ColorPickerSettingsWidget;

    d->widget->settingsToUI(d->generalSettings);

    return d->widget;
}

void ColorPickerOptionsPage::apply()
{
    GeneralSettings newGeneralSettings;
    d->widget->settingsFromUI(&newGeneralSettings);

    QSettings *s = Core::ICore::settings();

    if (d->generalSettings != newGeneralSettings) {
        d->generalSettings = newGeneralSettings;

        if (s)
            d->generalSettings.toSettings(d->settingsPrefix, s);

        emit generalSettingsChanged(newGeneralSettings);
    }
}

void ColorPickerOptionsPage::finish()
{
    delete d->widget;
}

} // namespace Internal
} // namespace ColorPicker
