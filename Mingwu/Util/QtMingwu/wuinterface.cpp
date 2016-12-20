#include "wuinterface.h"

wuInterface::wuInterface(QObject *parent) : QObject(parent)
{

}

QString wuInterface::loadFromeFile(const QString &str)
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
