#include "lib_controller.hpp"
#include "sort_container.hpp"
#include <QtConcurrent>
#include <iostream>

void Wrapper4Thread(LibController* cur_lib_ctrl, OrderBy order);

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

void LibController::fromFile(QString from_name){
    this->from_name = from_name.toUtf8().constData();
    this->fname_present = true;

    std::cout << this->from_name << std::endl;
}

void LibController::toFile(QString to_name){
    this->to_name = to_name.toUtf8().constData();
    this->tname_present = true;

    std::cout << this->to_name << std::endl;
}

void LibController::passToFileManager(){
    if(this->fname_present && this->tname_present){
        if(file_manager != nullptr){
            delete file_manager;
            file_manager = nullptr;
        }
        file_manager = new FileManager(this->from_name, this->to_name);
    }
    else{
        std::cout << "waiting for another file" << std::endl;
    }
}

void LibController::sortFile(LibController::Order order){
    if(this->fname_present && this->tname_present){
        switch(order){
            case LibController::Order::ASC:
                QtConcurrent::run(Wrapper4Thread, this, OrderBy::Asc);
                break;
            case LibController::Order::DESC:
                QtConcurrent::run(Wrapper4Thread, this, OrderBy::Desc);
                break;
        }
    }
    else{
        std::cout << "sorting was not started, because user did not supply all filenames" << std::endl;
    }
}

void Wrapper4Thread(LibController* cur_lib_ctrl, OrderBy order){ 
    //FileManager* working_fm = cur_lib_ctrl->file_manger;
    cur_lib_ctrl->file_manager->SortFile(order);
}

