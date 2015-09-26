// Qt includes
#include <QAction>
#include <QtTest>

// QtCreator includes
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/editormanager/editormanager.h>

#include <texteditor/texteditor.h>

// Own includes
#include "colormodifier.h"
#include "colorpickerconstants.h"
#include "colorpickerplugin.h"
#include "colorwatcher.h"

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {

void ColorPickerPlugin::test_addAndReplaceColor()
{
    QString fileName = QString::fromLatin1("test_ColorPickerPlugin_addAndReplaceColor.txt");
    QFile file(fileName);
    QVERIFY(file.open(QIODevice::ReadWrite | QIODevice::Text));

    IEditor *currentEditor = EditorManager::instance()->openEditor(fileName);
    QVERIFY(currentEditor);

    TextEditorWidget *editorWidget = qobject_cast<TextEditorWidget *>(currentEditor->widget());
    QVERIFY(editorWidget);

    Command *colorEditCommand = ActionManager::command(Constants::TRIGGER_COLOR_EDIT);

    QString color = QString::fromLatin1("rgb(12, 20, 40)");
    editorWidget->appendPlainText(color);

    QMap<ColorType, QColor> colors;
    colors.insert(ColorType::RgbType, QColor(32, 18, 26));
    colors.insert(ColorType::RgbaType, QColor(32, 18, 26, 127));
    colors.insert(ColorType::HsvType, QColor(32, 18, 26));
    colors.insert(ColorType::HsvaType, QColor(32, 18, 26, 127));
    colors.insert(ColorType::HexType, QColor(32, 18, 26));

    connect(m_colorWatcher, &ColorWatcher::colorFound,
            [=](const QColor &value, ColorType type) {
        qDebug() << type << value;
    });

    for (auto it = colors.begin(); it != colors.end();  ++it) {
        m_colorModifier->insertColor(it.value(), it.key());
        colorEditCommand->action()->trigger();
    }

    file.close();
}

} // namespace Internal
} // namespace ColorPicker
