#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include "lib_controller.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // Registration of custom type
    qmlRegisterType<LibController>("sorting", 1, 0, "LibController");

    QQmlApplicationEngine error_engine;
    const QUrl msg_url(QStringLiteral("qrc:/messages.qml"));
    LibController::error_reporter = QQmlComponent(&error_engine, msg_url).create();



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
