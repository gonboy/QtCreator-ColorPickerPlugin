#ifndef COLORWATCHER_H
#define COLORWATCHER_H

#include <QObject>

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

    void processCurrentTextCursor(TextEditor::TextEditorWidget *textEditor);

private:
    QScopedPointer<ColorWatcherImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORWATCHER_H
