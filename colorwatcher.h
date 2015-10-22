#ifndef COLORWATCHER_H
#define COLORWATCHER_H

#include <QObject>

#include "colorutilities.h"

namespace TextEditor {
class TextEditorWidget;
}

namespace ColorPicker {
namespace Internal {

class ColorWatcherImpl;

class ColorWatcher : public QObject
{
    Q_OBJECT

public:
    ColorWatcher(TextEditor::TextEditorWidget *textEditor);
    ~ColorWatcher();

    ColorCategory colorCategory() const;
    void setColorCategory(ColorCategory category);

    ColorExpr process();

private:
    QScopedPointer<ColorWatcherImpl> d;
};

} // namespace Internal
} // namespace ColorPicker

#endif // COLORWATCHER_H
