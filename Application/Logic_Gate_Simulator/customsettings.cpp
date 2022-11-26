#include "customsettings.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include "logger.h"

QDomDocument CustomSettings::m_doc;
QDomElement CustomSettings::m_parentElement;
bool CustomSettings::m_bLoaded;

CustomSettings::CustomSettings()
{
}

bool CustomSettings::init()
{
    QFileInfo fileInfo(Settings::SettingsFileName);
    QFile file(Settings::SettingsFileName);
    if(!fileInfo.exists())
    {
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            Logger::log(LogLevel::LL_FileError, "CustomSettings::init - Failed to create!");
            m_bLoaded = false;
            return false;
        }
        file.close();
    }

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        Logger::log(LogLevel::LL_FileError, "CustomSettings::init - Failed to load!");
        m_bLoaded = false;
        return false;
    }

    m_doc.setContent(&file);
    m_parentElement = m_doc.firstChildElement(Settings::SettingsXmlTag);

    if(m_parentElement.isNull())
    {
        m_parentElement = m_doc.createElement(Settings::SettingsXmlTag);
    }

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
    if(!nodes.isEmpty())
    {
        auto valueNode = nodes.at(0).firstChild().toText();
        const QString nodeValueText = valueNode.nodeValue();

        if(!nodeValueText.isEmpty())
        {
            return nodeValueText;
        }

        QDomElement settingElement = nodes.at(0).toElement();
        QDomText nodeTextDom = m_doc.createTextNode(defaultValue);
        settingElement.appendChild(nodeTextDom);
        m_parentElement.appendChild(settingElement);
        m_doc.appendChild(m_parentElement);
        return defaultValue;
    }

    QDomElement settingElement = m_doc.createElement(settingId);
    QDomText nodeValue = m_doc.createTextNode(defaultValue);
    settingElement.appendChild(nodeValue);

    m_parentElement.appendChild(settingElement);
    m_doc.appendChild(m_parentElement);

    return defaultValue;
}

void CustomSettings::writeSetting(const QString &settingId, const QString &value)
{
    auto nodes = m_parentElement.elementsByTagName(settingId);
    if(nodes.isEmpty())
    {
        QDomElement settingElement = m_doc.createElement(settingId);
        QDomText nodeValue = m_doc.createTextNode(value);
        settingElement.appendChild(nodeValue);

        m_parentElement.appendChild(settingElement);
        m_doc.appendChild(m_parentElement);
        return;
    }

    QDomElement settingElement = nodes.at(0).toElement();
    QDomElement settingElementReplace = m_doc.createElement(settingId);
    QDomText nodeTextDom = m_doc.createTextNode(value);
    settingElementReplace.appendChild(nodeTextDom);
    m_parentElement.replaceChild(settingElementReplace, settingElement);
    m_doc.appendChild(m_parentElement);
}
