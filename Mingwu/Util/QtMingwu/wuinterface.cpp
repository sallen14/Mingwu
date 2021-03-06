#include "wuinterface.h"

#include <string>
#include <fstream>

wuInterface::wuInterface(QObject *parent) : QObject(parent)
{
}

QString wuInterface::loadFromFile(const QString str)
{
    std::ifstream in(str.toStdString().c_str());

    if(!in.is_open())
    {
        auto rtn = "error: unable to load file " + str;
        return rtn;
    }

    char tmp[1024];
    while(!in.eof())
    {
        in.getline(tmp, 1024);
        _content += tmp;
        _content += "\n";
    }

    _file = str;
    return _content;
}

bool wuInterface::saveToFile(QString path, QString info)
{
    std::ofstream file;
    file.open(path.toStdString().c_str());
    file << info.toStdString();
    file.close();
    return false;
}

bool wuInterface::save(const QString path)
{
    std::ofstream file;
    file.open(path.toStdString().c_str());
    file << _content.toStdString();
    file.close();
    return false;
}

