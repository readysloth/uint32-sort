#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#include <vector>
#include "sort_container.hpp"

class FileManager{
    private:
        // Размер чанка для сортировки равен (размер_числа * 1МБ * 2)
        const size_t chunk_size = sizeof(NumberType)*1024*1024*2;

        // Инициализируется единицей так как в SortFile происходит
        // финальное упорядочивание файла
        decltype(std::ifstream.tellg()) remaining_chunks = 1;

        bool sort_occured = false;
        
        // Хранилище контейнеров с чанками
        std::vector<SortContainer*>     file_parts;
        decltype(std::ifstream.tellg()) filesize;
        std::string                     filename;
         
        void CopyFile(std::string from_name, std::string to_name);
        void DivideFile(size_t parts_cnt, size_t remainder_size);
    public:
        
        FileManager(std::string from_name, std::string to_name);
        ~FileManager();
        void SortFile(OrderBy order);

};

#endif
