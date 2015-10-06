#include "colorpickeroptionspage.h"

// Qt includes
#include <QCoreApplication>

// Plugin includes
#include "colorpickerconstants.h"
#include "widgets/colorpickersettingswidget.h"

namespace ColorPicker {
namespace Internal {

ColorPickerOptionsPage::ColorPickerOptionsPage(QObject *parent) :
    Core::IOptionsPage(parent)
{
    setId(Constants::COLORPICKER_SETTINGS_ID);
    setDisplayName(tr(Constants::COLORPICKER_SETTINGS_DISPLAY_NAME));
    setCategory(Constants::COLORPICKER_SETTINGS_CATEGORY);
    setDisplayCategory(QCoreApplication::translate("ColorPicker",
                                                   Constants::COLORPICKER_SETTINGS_TR_CATEGORY));
    setCategoryIcon(QLatin1String(Constants::COLORPICKER_SETTINGS_CATEGORY_ICON));
}

QWidget *ColorPickerOptionsPage::widget()
{
    if (!m_widget)
        m_widget = new ColorPickerSettingsWidget;

    return m_widget;
}

void ColorPickerOptionsPage::apply()
{
//    m_widget->saveSettings();
}

void ColorPickerOptionsPage::finish()
{
    delete m_widget;
}

} // namespace Internal
} // namespace ColorPicker
