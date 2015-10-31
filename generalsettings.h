#ifndef GENERALSETTINGS_H
#define GENERALSETTINGS_H

#include <QVariantMap>

class QSettings;

namespace ColorPicker {
namespace Internal {

class GeneralSettings
{
public:
    GeneralSettings();

    void toSettings(const QString &category, QSettings *s) const;
    void fromSettings(const QString &category, const QSettings *s);

    void toMap(const QString &prefix, QVariantMap *map) const;
    void fromMap(const QString &prefix, const QVariantMap &map);

    bool equals(const GeneralSettings &gs) const;

    /* variables */
    bool m_editorSensitive;
    bool m_insertOnChange;
};

inline bool operator==(const GeneralSettings &t1, const GeneralSettings &t2) { return t1.equals(t2); }
inline bool operator!=(const GeneralSettings &t1, const GeneralSettings &t2) { return !t1.equals(t2); }

} // namespace Internal
} // namespace ColorPicker

Q_DECLARE_METATYPE(ColorPicker::Internal::GeneralSettings)

#endif // GENERALSETTINGS_H
