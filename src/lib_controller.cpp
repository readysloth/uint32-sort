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
    /*if(file_manager != nullptr){
        delete file_manager;
        file_manager = nullptr;
    }*/
}

double LibController::getProgress(){

    double processed_chunks = this->file_manager->getProcessedChunks();
    double all_chunks = this->file_manager->getAllChunks();

    if(all_chunks != 0){
        this->current_progress = 1;
    }
    else{
        this->current_progress = processed_chunks/all_chunks;
    }

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
        /*if(file_manager != nullptr){
            delete file_manager;
            file_manager = nullptr;
        }*/

        try{
            file_manager = new FileManager(this->from_name, this->to_name);
        }
        catch(std::length_error &len_e){
            emit handleLenFail(); //"fileLen_fail"
        }
        catch(std::ios_base::failure &io_e){
            emit handleOpenFail(); //"fileOpen_fail"
        }
        catch(std::runtime_error &map_e){
            emit handleMapFail(); //"fileMap_fail"
        }
        catch(...){
            emit handleGenFail(); //"generic_fail"
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
    try{
        cur_lib_ctrl->file_manager->SortFile(cur_lib_ctrl->sort_order);
    }
    catch(std::length_error &len_e){
        emit cur_lib_ctrl->handleLenFail(); //"fileLen_fail"
    }
    catch(std::ios_base::failure &io_e){
        emit cur_lib_ctrl->handleOpenFail(); //"fileOpen_fail"
    }
    catch(std::runtime_error &map_e){
        emit cur_lib_ctrl->handleMapFail(); //"fileMap_fail"
    }
    catch(...){
        emit cur_lib_ctrl->handleGenFail(); //"generic_fail"
    }
}

