#ifndef WUINTERFACE_H
#define WUINTERFACE_H

#include <QObject>

class wuInterface : public QObject
{
    Q_OBJECT
public:
    explicit wuInterface(QObject *parent = 0);

signals:

public slots:
};

#endif // WUINTERFACE_H