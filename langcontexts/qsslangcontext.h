#ifndef QSSLANGCONTEXT_H
#define QSSLANGCONTEXT_H

#include "ilangcontext.h"

#include <QPointer>

class QAbstractButton;
class QButtonGroup;
class QPushButton;

namespace ColorPicker {
namespace Internal {

class QssLangContext : public ILangContext
{
    Q_OBJECT

public:
    explicit QssLangContext(QWidget *parent = 0);

    QString displayName() const override;
    void uncheck() override;

private slots:
    void translateToColorFormat(QAbstractButton *checkedBtn);

private:
    QButtonGroup *m_btnGroup;
    QPushButton *m_rgbBtn;
    QPushButton *m_rgbAlphaBtn;
    QPushButton *m_rgbPercentBtn;
    QPushButton *m_hsvBtn;
    QPushButton *m_hsvAlphaBtn;
    QPushButton *m_hexBtn;
};

} // namespace Internal
} // namespace ColorPicker

#endif // QSSLANGCONTEXT_H
