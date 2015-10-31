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
    m_editorSensitiveCheckBox(new QCheckBox(this)),
    m_insertOnChangeCheckBox(new QCheckBox(this))
{
    m_editorSensitiveCheckBox->setText(QLatin1String("Show the available formats according to the current editor."));
    m_insertOnChangeCheckBox->setText(QLatin1String("Insert text when the displayed color changes."));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_editorSensitiveCheckBox);
    mainLayout->addWidget(m_insertOnChangeCheckBox);
    mainLayout->addStretch();
}

ColorPickerSettingsWidget::~ColorPickerSettingsWidget()
{}

void ColorPickerSettingsWidget::settingsFromUI(GeneralSettings *settings)
{
    Q_ASSERT(settings);

    settings->m_editorSensitive = m_editorSensitiveCheckBox->isChecked();
    settings->m_insertOnChange = m_insertOnChangeCheckBox->isChecked();
}

void ColorPickerSettingsWidget::settingsToUI(const GeneralSettings settings)
{
    m_editorSensitiveCheckBox->setChecked(settings.m_editorSensitive);
    m_insertOnChangeCheckBox->setChecked(settings.m_insertOnChange);
}

} // namespace Internal
} // namespace ColorPicker
