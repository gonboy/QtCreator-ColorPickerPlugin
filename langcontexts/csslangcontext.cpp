#include "csslangcontext.h"

#include <QBoxLayout>
#include <QButtonGroup>
#include <QPushButton>

namespace ColorPicker {
namespace Internal {


////////////////////////// CssLangContext //////////////////////////

CssLangContext::CssLangContext(QWidget *parent) :
    ILangContext(parent),
    m_btnGroup(new QButtonGroup(this)),
    m_rgbBtn(new QPushButton(this)),
    m_rgbAlphaBtn(new QPushButton(this)),
    m_rgbPercentBtn(new QPushButton(this)),
    m_hslBtn(new QPushButton(this)),
    m_hslAlphaBtn(new QPushButton(this)),
    m_hexBtn(new QPushButton(this))
{
    // Build GUI
    m_rgbBtn->setText(QLatin1String("RGB"));
    m_rgbAlphaBtn->setText(QLatin1String("A"));
    m_rgbPercentBtn->setText(QLatin1String("%"));

    m_hslBtn->setText(QLatin1String("HSL"));
    m_hslAlphaBtn->setText(QLatin1String("A"));

    m_hexBtn->setText(QLatin1String("Hex"));

    m_rgbBtn->setCheckable(true);
    m_rgbAlphaBtn->setCheckable(true);
    m_rgbPercentBtn->setCheckable(true);
    m_hslBtn->setCheckable(true);
    m_hslAlphaBtn->setCheckable(true);
    m_hexBtn->setCheckable(true);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(m_rgbBtn, 0, 0);
    layout->addWidget(m_rgbAlphaBtn, 0, 1);
    layout->addWidget(m_rgbPercentBtn, 0, 2);

    layout->addWidget(m_hslBtn, 1, 0);
    layout->addWidget(m_hslAlphaBtn, 1, 1);

    layout->addWidget(m_hexBtn, 2, 0);

    // Create the exclusive group
    m_btnGroup->addButton(m_rgbBtn);
    m_btnGroup->addButton(m_hslBtn);
    m_btnGroup->addButton(m_hexBtn);

    // Connections
    connect(m_btnGroup, static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            this, &CssLangContext::translateToColorFormat);

    connect(m_rgbAlphaBtn, &QPushButton::toggled,
            [=](bool) {
        m_rgbBtn->click();
    });

    connect(m_rgbPercentBtn, &QPushButton::toggled,
            [=](bool) {
        m_rgbBtn->click();
    });

    connect(m_hslAlphaBtn, &QPushButton::toggled,
            [=](bool) {
        m_hslBtn->click();
    });
}

QString CssLangContext::displayName() const
{
    return QLatin1String("Css");
}

void CssLangContext::uncheck()
{
    m_rgbBtn->setChecked(false);
    m_hslBtn->setChecked(false);
}

void CssLangContext::translateToColorFormat(QAbstractButton *checkedBtn)
{
    ColorFormat format;

    if (checkedBtn == m_rgbBtn) {
        bool useAlpha = m_rgbAlphaBtn->isChecked();
        bool usePercents = m_rgbPercentBtn->isChecked();

        if (useAlpha) {
            if (usePercents)
                format = ColorFormat::QCssRgbaAlphaPercentType;
            else
                format = ColorFormat::QCssRgbaAlphaFloatType;
        }
        else {
            if (usePercents)
                format = ColorFormat::QCssRgbPercentType;
            else
                format = ColorFormat::QCssRgbType;
        }
    }
    else if (checkedBtn == m_hslBtn) {
        bool useAlpha = m_hslAlphaBtn->isChecked();

        if (useAlpha)
            format = ColorFormat::CssHslaType;
        else
            format = ColorFormat::CssHslType;
    }
    else if (checkedBtn == m_hexBtn)
        format = ColorFormat::HexType;

    emit formatChoosed(format);
}

} // namespace Internal
} // namespace ColorPicker
