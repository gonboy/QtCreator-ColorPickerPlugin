#ifndef COLORMODIFIER_H
#define COLORMODIFIER_H

#include <QObject>

#include "colorutilities.h"

namespace ColorPicker {
namespace Internal {

class ColorModifierImpl;

class ColorModifier : public QObject
{
    Q_OBJECT

public:
    explicit ColorModifier(QObject *parent = 0);
    ~ColorModifier();

    void insertColor(const QColor &newValue, ColorFormat asFormat);

private:
    QScopedPointer<ColorModifierImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORMODIFIER_H
