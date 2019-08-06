#ifndef LIB_CONTROLLER_HPP
#define LIB_CONTROLLER_HPP
#include <QObject>
#include <QString>
#include <QThread>
#include <string>

#include "file_manager.hpp"
#include "sort_container.hpp"


class LibController: public QObject {
    Q_OBJECT

    Q_PROPERTY(double progress READ getProgress)
    Q_PROPERTY(bool ready READ isReady)
    Q_PROPERTY(QString fileToSort WRITE setSortFile READ getSortFile)
    Q_PROPERTY(QString fileToSave READ getSaveFile)

    public:
        static QObject *error_reporter;
        explicit LibController(QObject *parent = 0);
        ~LibController(); 

        friend void Wrapper4Thread(LibController* cur_lib_ctrl); 
        
        /**************** Get/Set функции ***************/
        double getProgress();
        bool isReady();

        void setSortFile(QString from_name);
        Q_INVOKABLE
        void setSaveFile(QString folder, QString filename);
        QString getSortFile();
        QString getSaveFile();

        Q_INVOKABLE
        void setOrderAsc();
        Q_INVOKABLE
        void setOrderDesc();

        /*************** Функции-обертки над библиотекой ***************/
        Q_INVOKABLE
        void createFileManager();
        Q_INVOKABLE
        void sortFile();


    signals:
        void handleGenFail();   // Уведомление пользователя о неопознанной ошибке 
        void handleMapFail();   // Уведомление пользователя об ошибке отображения файла в память
        void handleLenFail();   // Уведомление пользователя об ошибке длины файла
        void handleOpenFail();  // Уведомление пользователя об ошибке открытия файла
        void handleNotReady();  // Уведомление пользователя о том, что нужно подождать
        void handleReady();     // Уведомление пользователя о том, что сортировка закончена

    private:
        double current_progress = 0;
        bool ready = true;
        
        bool fname_present = false;
        bool tname_present = false;

        OrderBy sort_order = OrderBy::Asc; // Стандартный порядок сортировки -- возрастающий

        std::string from_name;
        std::string to_name;

        FileManager* file_manager = nullptr;
};
#endif

