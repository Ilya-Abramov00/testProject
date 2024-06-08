#include "parser/xmlconfig.h"

#include <QString>
#include <iostream>


std::map<std::string, std::string> XmlConfigSettings::ConfigurationByFileName(const QString& name) {
    QString filename(dirsetting.absolutePath() + QDir::separator() + name);
    std::map<std::string, std::string> m;
    QFile f(filename);
    if(!f.exists() || !f.open(QFile::ReadOnly | QFile::Text)) {
        throw std::runtime_error("No such file ");
    }
    r.setDevice(&f);
    if(r.readNextStartElement()) {
        if(r.name() == "properties") {
            if(r.readNextStartElement() && r.name() == "prop")
                readPropElem(m);
            else
                std::cout << "Unknown configuration element "
                          << " in the file " << filename.toStdString();
        } else
            std::cout << "Unknown Base configuration element "
                      << " in the file " << filename.toStdString();
    }
    r.clear();
    return m;
}

void XmlConfigSettings::readPropElem(std::map<std::string, std::string>& m) {
    add2map(r.attributes(), m);
    if(r.readNext() == QXmlStreamReader::EndElement && r.readNextStartElement())
        readPropElem(m);
}

void XmlConfigSettings::add2map(const QXmlStreamAttributes& a, std::map<std::string, std::string>& m) {
    using namespace std;
    foreach(QXmlStreamAttribute attr, a)
        m.insert(pair<string, string>(attr.name().toString().toStdString(), attr.value().toString().toStdString()));
}
