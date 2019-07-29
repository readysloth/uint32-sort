#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP
#include <vector>
#include "sort_container.hpp"

class FileManager{
    private:
        const size_t chunk_size = 4096*4;
        bool sort_occured = false;
        std::vector<SortContainer*>      file_parts;
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
