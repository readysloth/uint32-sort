#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "lib_controller.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("Я все сам");
    app.setOrganizationDomain("example.org");
    app.setApplicationName("uint32_t sort");

    // Registration of custom type
    qmlRegisterType<LibController>("sorting", 1, 0, "LibController");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);


    return app.exec();
}
