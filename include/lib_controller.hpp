#ifndef LIB_CONTROLLER_HPP
#define LIB_CONTROLLER_HPP
#include <QObject>
#include <QString>
#include <QThread>

#include "file_manager.hpp"
#include "sort_container.hpp"


class LibController: public QObject {
    Q_OBJECT

    Q_PROPERTY(double progress READ getProgress)

    public:
        static QObject *error_reporter;
        explicit LibController(QObject *parent = 0);
        ~LibController(); 

        friend void Wrapper4Thread(LibController* cur_lib_ctrl); 
        double getProgress();
        bool isReady();

        Q_INVOKABLE
        void setFromFile(QString from_name);
        Q_INVOKABLE
        void setToFile(QString to_name);

        Q_INVOKABLE
        void passToFileManager();
        Q_INVOKABLE
        void sortFile();

        Q_INVOKABLE
        void setOrderAsc();
        Q_INVOKABLE
        void setOrderDesc();

    signals:
        void handleGenFail();
        void handleMapFail();
        void handleLenFail();
        void handleOpenFail();

    private:
        double current_progress;
        bool ready = false;
        
        bool fname_present = false;
        bool tname_present = false;
        OrderBy sort_order = OrderBy::Asc;

        std::string from_name;
        std::string to_name;

        FileManager* file_manager = nullptr;
};
#endif

