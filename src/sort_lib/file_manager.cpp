#include "file_manager.hpp"
#include <fstream>

void FileManager::CopyFile(std::string from_name, std::string to_name){
    std::ifstream  src(from_name, std::ios::binary);
    std::ofstream  dst(to_name,   std::ios::binary);

    dst << src.rdbuf();
    
    if (src.bad()){
        throw std::ios_base::failure("Error while reading " + from_name);
    }

    if (dst.bad()){
        throw std::ios_base::failure("Error while writing " + to_name);
    }

    this->filesize = src.tellg();
}

void FileManager::DivideFile(size_t parts_cnt, size_t remainder_size){
    off_t current_offset = 0;

    // В случае, если размер одного чанка больше, чем размер файла
    if (parts_cnt == 0 && remainder_size > 0){
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


    // В случае, если размер файла не кратен размеру чанка, 
    // то обрабатываем остаток отдельно
    if (remainder_size > 0){
        file_parts.push_back(new SortContainer(this->filename,
                                               remainder_size,
                                               current_offset));
        this->all_chunks++;
    }

    this->all_chunks += parts_cnt;

}

FileManager::FileManager(std::string from_name, std::string to_name){
    
    this->filename = to_name;

    this->CopyFile(from_name, to_name);

    size_t parts_cnt = this->filesize/chunk_size;
    size_t remainder_size = this->filesize % chunk_size;

    // Резервируем в векторе вычисленное количество элементов
    // для экономии операций релокации
    this->file_parts.reserve(parts_cnt);

    this->DivideFile(parts_cnt, remainder_size); 
}

FileManager::~FileManager(){
}

void FileManager::SortFile(OrderBy order){
    this->sort_occured = true; 
    
    // Параллельно сортируем все числа внутри чанков
    #pragma omp parallel for
    for(decltype(this->filesize) i = 0; i < this->file_parts.size(); i++){
        this->file_parts[i]->Sort(order);
        
        #pragma omp atomic
        this->processed_chunks++;
    }

    // Вызовет деструктор у каждого объекта, удаляя мапинг чанков файла на память
    this->file_parts.clear();
    
    
    // Сортируем файл от начала до конца
    SortContainer(this->filename,
                  this->filesize,
                  0).Sort(order);    
    

}

decltype(FileManager::processed_chunks) FileManager::getProcessedChunks(){
    return this->processed_chunks;
}

decltype(FileManager::processed_chunks) FileManager::getAllChunks(){
    return this->all_chunks;
}
