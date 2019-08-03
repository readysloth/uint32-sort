#include "lib_controller.hpp"
#include "sort_container.hpp"

LibController::LibController(QObject *parent) : QObject(parent) {
}

LibController::~LibController(){
    delete file_manager;
}

double LibController::getProgress(){
    return this->current_progress;
}

void LibController::addFile(QString from_name, QString to_name){
    file_manager = new FileManager(from_name.toUtf8().constData(),
                                   to_name.toUtf8().constData());
}

void LibController::sortFile(){
    this->file_manager->SortFile(OrderBy::Asc);
}
