#ifndef DRAWHELPERS_H
#define DRAWHELPERS_H

#include <QImage>

namespace ColorPicker {
namespace Internal {

QImage opacityCheckerboard(const QRect &rect, int squareSide);

} // namespace Internal
} // namespace ColorPicker

#endif // DRAWHELPERS_H
