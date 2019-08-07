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

/**************** Get/Set функции ***************/

/**** Возвращает значение, говорящее о том, готов ли контроллер принять новый файл ****/
bool LibController::isReady(){
    return this->ready;
}

/**** Возвращает прогресс сортировки ****/
/* 
 * Это количество обработанных чанков, деленое на общее количество чанков
 *
 */
double LibController::getProgress(){

    double processed_chunks;
    double all_chunks;

    if(this->file_manager != nullptr){
        processed_chunks = this->file_manager->getProcessedChunks();
        all_chunks = this->file_manager->getAllChunks();
    }

    if(all_chunks != 0){
        this->current_progress = 1;
    }
    else{
        this->current_progress = processed_chunks/all_chunks;
    }

    return this->current_progress;
}

/**** Сеттеры имен файлов ****/

void LibController::setSortFile(QString from_name){
    this->from_name = from_name.toUtf8().constData();
    this->fname_present = true;

    std::cout << this->from_name << std::endl;
}

void LibController::setSaveFile(QString folder, QString filename){
    this->to_name = (folder.toUtf8() +
                    filename.toUtf8().constData() + ".sorted").constData();
    this->tname_present = true;

    std::cout << this->to_name << std::endl;
}

/**** Геттеры имен файлов ****/

QString LibController::getSortFile(){
   return QString::fromUtf8(this->from_name.c_str());
}

QString LibController::getSaveFile(){
   return QString::fromUtf8(this->to_name.c_str());
}

/**** Сеттеры порядка сортировки ****/

void LibController::setOrderAsc(){
    this->sort_order = OrderBy::Asc;
}

void LibController::setOrderDesc(){
    this->sort_order = OrderBy::Desc;
}

/*************** Функции-обертки над библиотекой ***************/

void LibController::createFileManager(){
    if(!this->ready){
        emit handleNotReady();
    }
    if(this->fname_present && this->tname_present){
        if(this->file_manager != nullptr){
            delete this->file_manager;
            this->file_manager = nullptr;
        }

        try{
            file_manager = new FileManager(this->from_name, this->to_name);
        }
        catch(std::length_error &len_e){
            emit handleLenFail();
        }
        catch(std::ios_base::failure &io_e){
            emit handleOpenFail();
        }
        catch(std::runtime_error &map_e){
            emit handleMapFail();
        }
        catch(...){
            emit handleGenFail();
        }
    }
    else{
        std::cout << "waiting for another file" << std::endl;
    }
}

void LibController::sortFile(){
    if(this->fname_present && this->tname_present){

        // Запрещаем любые действия c котроллером
        this->ready = false;
        // Запускаем сортировку в отдельном потоке
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
        emit cur_lib_ctrl->handleLenFail();
    }
    catch(std::ios_base::failure &io_e){
        emit cur_lib_ctrl->handleOpenFail();
    }
    catch(std::runtime_error &map_e){
        emit cur_lib_ctrl->handleMapFail();
    }
    catch(...){
        emit cur_lib_ctrl->handleGenFail();
    }

    cur_lib_ctrl->ready = true;

    emit cur_lib_ctrl->handleReady();
}

