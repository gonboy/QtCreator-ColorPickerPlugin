#include "colorpickersettingswidget.h"

// Qt includes
#include <QBoxLayout>
#include <QCheckBox>

// Plugin includes
#include "../generalsettings.h"

namespace ColorPicker {
namespace Internal {

ColorPickerSettingsWidget::ColorPickerSettingsWidget(QWidget *parent) :
    QWidget(parent)
{

}

ColorPickerSettingsWidget::~ColorPickerSettingsWidget()
{}

void ColorPickerSettingsWidget::settingsFromUI(GeneralSettings *settings)
{
    Q_ASSERT(settings);
}

void ColorPickerSettingsWidget::settingsToUI(const GeneralSettings settings)
{
}

} // namespace Internal
} // namespace ColorPicker
