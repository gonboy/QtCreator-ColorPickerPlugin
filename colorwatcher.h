#ifndef TEXTEDITORWATCHER_H
#define TEXTEDITORWATCHER_H

#include <QObject>

namespace ColorPicker {
namespace Internal {

class ColorWatcherImpl;

class ColorWatcher : public QObject
{
public:
    ColorWatcher(QObject *parent = 0);

signals:

public slots:
    void onCursorPositionChanged();

private:
    QScopedPointer<ColorWatcherImpl> d;
};

} // namespace ColorPicker
} // namespace Internal

#endif // TEXTEDITORWATCHER_H
