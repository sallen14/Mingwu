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


    QString _file;
    QString _content;

    Q_INVOKABLE QString loadFromeFile(const QString& str);
signals:

public slots:
};

#endif // WUINTERFACE_H
