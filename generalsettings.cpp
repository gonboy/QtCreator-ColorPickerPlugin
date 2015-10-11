#include "generalsettings.h"

#include <QDebug>

#include <utils/settingsutils.h>

namespace ColorPicker {
namespace Internal {

static const char groupPostfix[] = "GeneralSettings";

GeneralSettings::GeneralSettings()
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
}

void GeneralSettings::fromMap(const QString &prefix, const QVariantMap &map)
{
}

bool GeneralSettings::equals(const GeneralSettings &gs) const
{
    return true;
}

} // namespace Internal
} // namespace ColorPicker
