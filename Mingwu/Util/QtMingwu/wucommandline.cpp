#include "wucommandline.h"

wuCommandLine::wuCommandLine(QObject *parent) : QObject(parent)
{

}

wuCommandLine::wuCommandLine(QString cmd)
{
    _cmd = cmd;
}

void wuCommandLine::exe()
{
    std::FILE *in; //file to store command output
    char buff[512];//buffer use to filter/ use to convert command output
    if(!open(in, _cmd))//executes command
    {
        return;//return if failed
    }
    while(fgets(buff, sizeof(buff), in)!=NULL)//extract command output
    {
        _err += buff;//add buffer to error container
    }
    pclose(in);//close the open file
}

void wuCommandLine::exe(QString cmd)
{
    std::FILE *in;
    char buff[512];
    if(!open(in, cmd))
    {
        return;
    }
    while(fgets(buff, sizeof(buff), in)!=NULL)
    {
        _err += buff;
    }
    pclose(in);
}

QString wuCommandLine::exec(QString cmd)
{
    std::FILE *in = NULL;
    int status;
    char buff[2048];

#ifdef WIN32//Windows code
    if(!(in = _popen(cmd.toStdString().c_str(), "r")))
    {
        _err += "Failed:" + cmd;//fail to open process

        return getErr();
    }
    //fetch command errors
    while(fgets(buff, sizeof(buff), in)!=NULL)
    {
        _err += buff;
    }
    status = pclose(in);

    if(status == -1)
    {
        _err += "Error: Invalid Command";
    }
#elif __linux__//Linux/OSX code

    try{
        //try to open shell
        in = openShell(cmd.toStdString().c_str(), "e");
    }
    catch(const std::exception& e)
    {
        _err = e.what();
    }

    if((in) != NULL)
    {
        //fetch command errors
        while(fgets(buff, sizeof(buff), in)!= 0)
        {
            _err += buff;
        }

        status = closeShell(in);

    }
    else
    {
        status = closeShell(in);
        _err += "Failed:" + cmd;

        return getErr();
    }
    if(status == -1)
    {
        _err += "Error: Invalid Command";
    }
#endif
    return getErr();
}

bool wuCommandLine::open(std::FILE *intern, QString cmd)
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
