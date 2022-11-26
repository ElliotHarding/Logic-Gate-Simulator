#include "customsettings.h"
#include <QFile>
#include <QTextStream>
#include "logger.h"

QDomDocument m_doc;
QDomElement m_parentElement;
bool m_bLoaded;

CustomSettings::CustomSettings()
{
}

bool CustomSettings::init()
{
    QFile file(Settings::SettingsFileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        Logger::log(LogLevel::LL_FileError, "CustomSettings::init - Failed to load!");
        m_bLoaded = false;
        return false;
    }

    m_doc.setContent(&file);
    m_parentElement = m_doc.firstChildElement(Settings::SettingsXmlTag);

    m_bLoaded = true;
    return true;
}

bool CustomSettings::close()
{
    QFile file(Settings::SettingsFileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        Logger::log(LogLevel::LL_FileError, "CustomSettings::close - Failed to save!");
        return false;
    }

    if(!m_bLoaded)
    {
        return false;
    }

    m_doc.appendChild(m_parentElement);

    QTextStream stream(&file);
    stream << m_doc.toString();

    file.close();
    return true;
}

QString CustomSettings::readSetting(const QString& settingId, const QString& defaultValue)
{
    auto nodes = m_parentElement.elementsByTagName(settingId);
    if(nodes.isEmpty())
    {
        QDomElement settingElement = m_doc.createElement(settingId);

        settingElement.setNodeValue(defaultValue);

        m_parentElement.appendChild(settingElement);
        return defaultValue;
    }

    return nodes.at(0).nodeValue();
}

void CustomSettings::writeSetting(const QString &settingId, const QString &value)
{
    auto nodes = m_parentElement.elementsByTagName(settingId);
    if(nodes.isEmpty())
    {
        QDomElement settingElement = m_doc.createElement(settingId);

        settingElement.setNodeValue(value);

        m_parentElement.appendChild(settingElement);
        return;
    }

    nodes.at(0).setNodeValue(value);
}
