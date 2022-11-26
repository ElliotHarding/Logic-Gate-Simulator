#ifndef CUSTOMSETTINGS_H
#define CUSTOMSETTINGS_H

#include <QString>
#include <QDomDocument>

namespace Settings
{
const QString SettingsFileName = "Settings.xml";
const QString SettingsXmlTag = "Settings";
}

class CustomSettings
{
public:
    CustomSettings();

    static bool init();
    static bool close();

    static QString readSetting(const QString& settingId, const QString& defaultValue);
    static void writeSetting(const QString& settingId, const QString& value);

private:
    static QDomDocument m_doc;
    static QDomElement m_parentElement;
    static bool m_bLoaded;
};

#endif // CUSTOMSETTINGS_H
