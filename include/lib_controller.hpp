#ifndef LIB_CONTROLLER_HPP
#define LIB_CONTROLLER_HPP
#include <QObject>
#include <QString>
#include "file_manager.hpp"
#include "sort_container.hpp"

class LibController : public QObject{
    Q_OBJECT
    Q_PROPERTY(decltype(getProgress) progress READ getProgress NOTIFY ProgressChanged)
    public:
        explicit LibController(QObject *parent = 0);
        ~LibController(); 

        double getProgress();

        Q_INVOKABLE
        void addFile(QString from_name, QString to_name);
        Q_INVOKABLE
        void sortFile();
    signals:
        void ProgressChanged();

    private:
        double current_progress;
        FileManager* file_manager;
};
#endif
