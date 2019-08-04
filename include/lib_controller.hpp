#ifndef LIB_CONTROLLER_HPP
#define LIB_CONTROLLER_HPP
#include <QObject>
#include <QString>
#include <QThread>
#include "file_manager.hpp"
#include "sort_container.hpp"


class LibController: public QObject {
    Q_OBJECT

    Q_PROPERTY(double progress READ getProgress NOTIFY ProgressChanged)
    Q_PROPERTY(bool ready READ isReady)
    Q_ENUMS(Order)

    public:
        enum Order{
            ASC,
            DESC
        };

        explicit LibController(QObject *parent = 0);
        ~LibController(); 

        double getProgress();
        bool isReady();

        Q_INVOKABLE
        void fromFile(QString from_name);
        Q_INVOKABLE
        void toFile(QString to_name);

        Q_INVOKABLE
        void passToFileManager();
        Q_INVOKABLE
        void sortFile(LibController::Order order);
    signals:
        void ProgressChanged();

    private:
        QThread thread;
        double current_progress;
        bool ready = false;
        
        bool fname_present = false;
        bool tname_present = false;

        std::string from_name;
        std::string to_name;

        FileManager* file_manager = nullptr;
};
#endif
