#include "wucommandline.h"

wuCommandLine::wuCommandLine(QObject *parent) : QObject(parent)
{

}

wuCommandLine::wuCommandLine(QString cmd)
{
    _cmd = cmd;
}

bool wuCommandLine::open(FILE *intern, QString cmd)
{
#ifdef WIN32//Windows code
    if(!(intern = _popen(cmd.toStdString().c_str(), "r")))
    {
        return false;//fail to open process
    }
#else//Linux/OSX code
    if(!(intern = popen(cmd.toStdString().c_str(), "r")))
    {
        return false;
    }
#endif
    return true;//successful open process
}
