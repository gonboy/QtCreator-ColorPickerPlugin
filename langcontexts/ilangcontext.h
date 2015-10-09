#ifndef ILANGCONTEXT_H
#define ILANGCONTEXT_H

#include <QWidget>

#include "../colorpicker_global.h"

class QWidget;

namespace ColorPicker {
namespace Internal {

class ILangContext : public QWidget
{
    Q_OBJECT

public:
    explicit ILangContext(QWidget *parent = 0);

    virtual QString displayName() const = 0;
    virtual void uncheck() = 0;

signals:
    void formatChoosed(ColorFormat);
};

} // namespace Internal
} // namespace ColorPicker

#endif // ILANGCONTEXT_H
