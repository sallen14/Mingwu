#ifndef WUINTERFACE_H
#define WUINTERFACE_H

#include <QObject>

#include <string>
#include <fstream>

using namespace std;

class wuInterface : public QObject
{
    Q_OBJECT
public:
    explicit wuInterface(QObject *parent = 0);


    QString _file;//store file path
    QString _content;//store file contents
    //Function:loads file content
    Q_INVOKABLE QString loadFromeFile(const QString& str);
    //Function:saves data to file with given path and content
    Q_INVOKABLE virtual bool saveToFile(QString path, QString info);
    //Function:saves data to file with given path
    Q_INVOKABLE virtual bool save(const QString& path);
signals:

public slots:
};

#endif // WUINTERFACE_H
