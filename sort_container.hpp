#ifndef SORT_CONTAINER_HPP
#define SORT_CONTAINER_HPP
#include <cstdint>
#include <string>

using NumberType = uint32_t;

enum OrderBy {Asc, Desc};

class SortContainer final{
    private:
        // Указатель на часть файла, замапленного через mmap
        NumberType* file_contents;
        // Количество чисел в fileContents
        size_t count;
        //void Swap(NumberType& l, NumberType& r);
    public:
       SortContainer(std::string filename, size_t size_to_map, off_t offset);
       ~SortContainer();

       void Sort(OrderBy order);
};

#endif
