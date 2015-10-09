#ifndef CSSLANGCONTEXT_H
#define CSSLANGCONTEXT_H

#include "ilangcontext.h"

class QAbstractButton;
class QButtonGroup;
class QPushButton;

namespace ColorPicker {
namespace Internal {

class CssLangContext : public ILangContext
{
    Q_OBJECT

public:
    explicit CssLangContext(QWidget *parent = 0);

    QString displayName() const override;
    void uncheck() override;

private slots:
    void translateToColorFormat(QAbstractButton *checkedBtn);

private:
    QButtonGroup *m_btnGroup;
    QPushButton *m_rgbBtn;
    QPushButton *m_rgbAlphaBtn;
    QPushButton *m_rgbPercentBtn;
    QPushButton *m_hslBtn;
    QPushButton *m_hslAlphaBtn;
    QPushButton *m_hexBtn;
};

} // namespace Internal
} // namespace ColorPicker

#endif // CSSLANGCONTEXT_H
