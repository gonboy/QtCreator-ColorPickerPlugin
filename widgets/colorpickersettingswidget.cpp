#include "colorpickersettingswidget.h"

// Qt includes
#include <QBoxLayout>
#include <QCheckBox>

// Plugin includes
#include "../generalsettings.h"

namespace ColorPicker {
namespace Internal {

ColorPickerSettingsWidget::ColorPickerSettingsWidget(QWidget *parent) :
    QWidget(parent),
    m_editorSensitiveCheckBox(new QCheckBox(this))
{
    m_editorSensitiveCheckBox->setText(QLatin1String("Show the available formats according to the current editor."));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_editorSensitiveCheckBox);
    mainLayout->addStretch();
}

ColorPickerSettingsWidget::~ColorPickerSettingsWidget()
{}

void ColorPickerSettingsWidget::settingsFromUI(GeneralSettings *settings)
{
    Q_ASSERT(settings);

    settings->m_editorSensitive = m_editorSensitiveCheckBox->isChecked();
}

void ColorPickerSettingsWidget::settingsToUI(const GeneralSettings settings)
{
    m_editorSensitiveCheckBox->setChecked(settings.m_editorSensitive);
}

} // namespace Internal
} // namespace ColorPicker
