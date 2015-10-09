#ifndef COLORMODIFIER_H
#define COLORMODIFIER_H

#include <QObject>

#include "colorpicker_global.h"

namespace ColorPicker {
namespace Internal {

class ColorModifierImpl;

class ColorModifier : public QObject
{
    Q_OBJECT

public:
    explicit ColorModifier(QObject *parent = 0);
    ~ColorModifier();

    void insertColor(const QColor &newValue, ColorFormat asType);

private:
    QScopedPointer<ColorModifierImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORMODIFIER_H
