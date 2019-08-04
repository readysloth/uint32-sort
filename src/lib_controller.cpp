#include <QtConcurrent>
#include <QQmlComponent>
#include <QMetaObject>

#include <iostream>
#include <stdexcept>
#include <ios>

#include "lib_controller.hpp"
#include "sort_container.hpp"

void Wrapper4Thread(LibController* cur_lib_ctrl);

QObject* LibController::error_reporter;

LibController::LibController(QObject *parent) : QObject(parent) { }

LibController::~LibController(){
    if(file_manager != nullptr){
        delete file_manager;
        file_manager = nullptr;
    }
}

double LibController::getProgress(){
    current_progress = static_cast<double>(this->file_manager->getProcessedChunks())/this->file_manager->getAllChunks();

    return this->current_progress;
}

bool LibController::isReady(){
    return this->ready;
}

void LibController::setFromFile(QString from_name){
    this->from_name = from_name.toUtf8().constData();
    this->fname_present = true;

    std::cout << this->from_name << std::endl;
}

void LibController::setToFile(QString to_name){
    this->to_name = to_name.toUtf8().constData();
    this->tname_present = true;

    std::cout << this->to_name << std::endl;
}

void LibController::setOrderAsc(){
    this->sort_order = OrderBy::Asc;
}

void LibController::setOrderDesc(){
    this->sort_order = OrderBy::Desc;
}

void LibController::passToFileManager(){
    if(this->fname_present && this->tname_present){
        if(file_manager != nullptr){
            delete file_manager;
            file_manager = nullptr;
        }

        try{
            file_manager = new FileManager(this->from_name, this->to_name);
        }
        catch(std::length_error &len_e){
            QMetaObject::invokeMethod(LibController::error_reporter->findChild<QObject *>("fileLen_fail"),
                                      "open");
        }
        catch(std::ios_base::failure &io_e){
            QMetaObject::invokeMethod(LibController::error_reporter->findChild<QObject *>("fileOpen_fail"),
                                      "open");
        }
        catch(std::runtime_error &map_e){
            QMetaObject::invokeMethod(LibController::error_reporter->findChild<QObject *>("fileMap_fail"),
                                      "open");
        }
    }
    else{
        std::cout << "waiting for another file" << std::endl;
    }
}

void LibController::sortFile(){
    if(this->fname_present && this->tname_present){
        QtConcurrent::run(Wrapper4Thread, this);
    }
    else{
        std::cout << "sorting was not started, because user did not supply all filenames" << std::endl;
    }
}

void Wrapper4Thread(LibController* cur_lib_ctrl){ 
    cur_lib_ctrl->file_manager->SortFile(cur_lib_ctrl->sort_order);
}

