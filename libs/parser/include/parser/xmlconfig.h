#pragma once

#include <QDir>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>

class XmlConfigSettings {
public:
    XmlConfigSettings() { }
    ~XmlConfigSettings() { }
    std::map<std::string, std::string> ConfigurationByName(const QString& name);
    std::map<std::string, std::string> ConfigurationByFileName(const QString& name);

private:
    bool isValid(const QString& file);
    void readPropElem(std::map<std::string, std::string>& m);
    void add2map(const QXmlStreamAttributes& a, std::map<std::string, std::string>& m);
    QXmlStreamReader r;
    QFile currfile;
    QDir dirsetting;
};
