#pragma once

#include <QDir>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>

class XmlConfigSettings {
public:
    std::map<std::string, std::string> ConfigurationByFileName(const QString& name);

private:
    void readPropElem(std::map<std::string, std::string>& m);
    void add2map(const QXmlStreamAttributes& a, std::map<std::string, std::string>& m);
    QXmlStreamReader r;
    QFile currfile;
    QDir dirsetting;
};
