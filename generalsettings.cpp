#include "generalsettings.h"

#include <QDebug>

#include <utils/settingsutils.h>

namespace ColorPicker {
namespace Internal {

static const char groupPostfix[] = "GeneralSettings";
static const char editorSensitiveKey[] = "EditorSensitive";
static const char insertOnChangeKey[] = "InsertOnChange";

GeneralSettings::GeneralSettings() :
    m_editorSensitive(true),
    m_insertOnChange(true)
{}

void GeneralSettings::toSettings(const QString &category, QSettings *s) const
{
    Utils::toSettings(QLatin1String(groupPostfix), category, s, this);
}

void GeneralSettings::fromSettings(const QString &category, const QSettings *s)
{
    *this = GeneralSettings(); // Assign defaults
    Utils::fromSettings(QLatin1String(groupPostfix), category, s, this);
}

void GeneralSettings::toMap(const QString &prefix, QVariantMap *map) const
{
    map->insert(prefix + QLatin1String(editorSensitiveKey), m_editorSensitive);
    map->insert(prefix + QLatin1String(insertOnChangeKey), m_insertOnChange);
}

void GeneralSettings::fromMap(const QString &prefix, const QVariantMap &map)
{
    m_editorSensitive = map.value(prefix + QLatin1String(editorSensitiveKey),
                                  m_editorSensitive).toBool();
    m_insertOnChange = map.value(prefix + QLatin1String(insertOnChangeKey),
                                 m_insertOnChange).toBool();
}

bool GeneralSettings::equals(const GeneralSettings &gs) const
{
    if (m_editorSensitive != gs.m_editorSensitive)
        return false;

    if (m_insertOnChange != gs.m_insertOnChange)
        return false;

    return true;
}

} // namespace Internal
} // namespace ColorPicker
