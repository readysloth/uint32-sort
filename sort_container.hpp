#ifndef SORT_CONTAINER_HPP
#define SORT_CONTAINER_HPP
#include <map>
#include <cstdint>
#include <string>

void CopyFile(std::string from_name, std::string to_name);

class SortContainer final{
    private:
        // Указатель на часть файла, замапленного через mmap
        uint32_t* file_contents;
        // Количество чисел в fileContents
        uint64_t count;
        Swap(&uint32_t l, &uint32_t r)
    public:
       SortContainer(std::string filename, size_t size_to_map, off_t offset);
       ~SortContainer();

       MergeSort();
}

#endif
