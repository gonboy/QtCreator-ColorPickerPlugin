#include "colormodifier.h"

// Qt includes
#include <QDebug>
#include <QTextBlock>
#include <QTextCursor>

// QtCreator includes
#include <coreplugin/editormanager/editormanager.h>

#include <texteditor/texteditor.h>

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorModifierImpl //////////////////////////

class ColorModifierImpl
{
public:
    ColorModifierImpl();

    /* functions */
};

ColorModifierImpl::ColorModifierImpl()
{

}


////////////////////////// ColorModifier //////////////////////////

ColorModifier::ColorModifier(QObject *parent) :
    QObject(parent),
    d(new ColorModifierImpl)
{

}

ColorModifier::~ColorModifier()
{}

void ColorModifier::insertColor(const QColor &newValue, ColorFormat asFormat)
{
    IEditor *currentEditor = EditorManager::instance()->currentEditor();
    if (!currentEditor)
        return;

    TextEditorWidget *editorWidget = qobject_cast<TextEditorWidget *>(currentEditor->widget());
    QTextCursor currentCursor = editorWidget->textCursor();

    QString newText = colorToString(newValue, asFormat);

    currentCursor.insertText(newText);
    currentCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor,
                               newText.size());
    currentCursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor,
                               newText.size());

    editorWidget->setTextCursor(currentCursor);
}

} // namespace Internal
} // namespace ColorPicker
