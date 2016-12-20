#ifndef WUINTERFACE_H
#define WUINTERFACE_H

#include <QObject>

#include <QString>

//using namespace std;

class wuInterface : public QObject
{
    Q_OBJECT
public:
    explicit wuInterface(QObject *parent = 0);


    QString _file;//store file path
    QString _content;//store file contents
    //Function:loads file content
    Q_INVOKABLE QString loadFromFile(const QString str);
    //Function:saves data to file with given path and content
    Q_INVOKABLE virtual bool saveToFile(QString path, QString info);
    //Function:saves data to file with given path
    Q_INVOKABLE virtual bool save(const QString path);

    //Function:parse file data to given structure
    Q_INVOKABLE virtual bool parse(){ return false;}
    //Function:parse file data to given structure
    Q_INVOKABLE virtual bool parse(const QString path){ if(path.toStdString().empty())return false;return false;}

signals:

public slots:
};

#endif // WUINTERFACE_H
