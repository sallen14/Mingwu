#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include <Util/QtMingwu/wuinterface.h>
#include <Util/QtMingwu/wucommandline.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    //Make C++ classes accessable to qml
    //QScopedPointer<Class> var(new Class);
    QScopedPointer<wuInterface> inter(new wuInterface);
    QScopedPointer<wuCommandLine> cmd(new wuCommandLine);

    //wu_Interface i;
    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    //Set qml context properties
    engine.rootContext()->setContextProperty("inter", inter.data());
    engine.rootContext()->setContextProperty("commandline", cmd.data());



    return app.exec();
}
