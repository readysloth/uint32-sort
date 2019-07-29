#include "file_manager.hpp"
#include <fstream>

void FileManager::CopyFile(std::string from_name, std::string to_name){
    std::ifstream  src(from_name, std::ios::binary);
    std::ofstream  dst(to_name,   std::ios::binary);

    dst << src.rdbuf();

    this->filesize = src.tellg();
}

void FileManager::DivideFile(size_t parts_cnt, size_t remainder_size){
    off_t current_offset = 0;

    // В случае, если размер одного чанка больше, чем размер файла
    if (parts_cnt == 0){
        parts_cnt = 1;
        this->file_parts.push_back(new SortContainer(this->filename,
                                                     remainder_size,
                                                     0));
        return;
    }    
    
    // Инициализация контейнеров для всех чанков 
    for(decltype(parts_cnt) i = 0; i < parts_cnt; i++){
        file_parts.push_back(new SortContainer(this->filename,
                                               this->chunk_size,
                                               current_offset));
        current_offset += this->chunk_size;
    }

    // В случае, если размер файла не кратен чанку, 
    // то обрабатываем остаток отдельно
    if (remainder_size > 0){
        file_parts.push_back(new SortContainer(this->filename,
                                               remainder_size,
                                               current_offset));
    }

}

FileManager::FileManager(std::string from_name, std::string to_name){

    this->filename = to_name;

    this->CopyFile(from_name, to_name);

    size_t parts_cnt = this->filesize/chunk_size;
    size_t remainder_size = this->filesize % chunk_size;

    this->file_parts.reserve(parts_cnt);

    this->DivideFile(parts_cnt, remainder_size); 
}

FileManager::~FileManager(){
    /*
     if(!this->sort_occured)
        delete this->file_parts;
     */
}

void FileManager::SortFile(OrderBy order){
    this->sort_occured = true; 
    
    // Параллельно сортируем все числа внутри чанков

    #pragma omp parallel for
    for(decltype(this->filesize) i = 0; i < this->file_parts.size(); i++){
        this->file_parts[i]->Sort(order);
    }

    this->file_parts.clear();
    
    
    // Сортируем все чанки файла
    SortContainer(this->filename,
                  this->filesize,
                  0).Sort(order);    
    

}
