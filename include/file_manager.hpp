#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#include <vector>
#include <fstream>
#include "sort_container.hpp"

class FileManager{
    private:
        // Размер чанка для сортировки равен (размер_числа * 1МБ * 2)
        const size_t chunk_size = sizeof(NumberType)*1024*1024*2;

        // Инициализируется единицей так как в SortFile происходит
        // финальное упорядочивание файла
        size_t processed_chunks = 0;
        decltype(processed_chunks) all_chunks = 0;

        bool sort_occured = false;
        
        // Хранилище контейнеров с чанками
        std::vector<SortContainer*>  file_parts;
        size_t                       filesize;
        std::string                  filename;
         
        // Функция, копирующая файл
        void CopyFile(std::string from_name, std::string to_name);

        // Функция, делящая файл на чанки и инициализирующая контейнеры сортировки
        void DivideFile(size_t parts_cnt, size_t remainder_size);
    public:
        
        FileManager(std::string from_name, std::string to_name);
        ~FileManager();

        // Функция, начинающая сортировку файла
        void SortFile(OrderBy order);

        decltype(processed_chunks) getProcessedChunks();
        decltype(all_chunks) getAllChunks();

};

#endif
