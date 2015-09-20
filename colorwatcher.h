#ifndef TEXTEDITORWATCHER_H
#define TEXTEDITORWATCHER_H

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

} // namespace ColorPicker
} // namespace Internal

#endif // TEXTEDITORWATCHER_H
