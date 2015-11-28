#include "drawhelpers.h"

#include <QDebug>
#include <QPainter>

namespace ColorPicker {
namespace Internal {

QImage opacityCheckerboard(const QRect &rect, int squareSide)
{
    QPixmap pix(rect.size());
    pix.fill();

    QPainter painter(&pix);
    painter.setPen(QPen(Qt::NoPen));
    painter.setBrush(Qt::gray);

    int xSquareCount = rect.width() / squareSide;
    int ySquareCount = rect.height() / squareSide;

    QSize squareSize(squareSide, squareSide);
    QPoint currentTopLeft;

    for (int i = 0; i <= xSquareCount; ++i)
    {
        bool isOnAlternateRow = (i % 2);

        for (int j = 0; j < ySquareCount; ++j)
        {
            bool drawRect = ( (j % 2) && isOnAlternateRow )
                    || ( !(j % 2) && !isOnAlternateRow);

            if (drawRect)
                painter.drawRect(QRect(currentTopLeft, squareSize));

            currentTopLeft.ry() += squareSide;
        }

        currentTopLeft.rx() += squareSide;
        currentTopLeft.ry() = 0;
    }

    return pix.toImage();
}

} // namespace Internal
} // namespace ColorPicker
