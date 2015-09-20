#ifndef COLORWATCHER_H
#define COLORWATCHER_H

#include <QObject>

#include <texteditor/texteditor.h>

namespace TextEditor {
class TextEditorWidget;
}

namespace ColorPicker {
namespace Internal {

class ColorWatcherImpl;

class ColorWatcher : public QObject
{
public:
    ColorWatcher(QObject *parent = 0);

    void addEditor(TextEditor::TextEditorWidget *editor);

signals:

public slots:
    void onCursorPositionChanged();

private:
    QScopedPointer<ColorWatcherImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORWATCHER_H
