#include <stdexcept>
#include <ios>
#include <cstdlib>

#ifdef unix

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#endif

#ifdef _WIN32

#error Native windows compiltion is currently unsupported. Wait or try compile with Cygwin

#endif

#include "sort_container.hpp"


SortContainer::SortContainer(std::string filename, size_t size_to_map, size_t offset){
    
    // Проверка на корректность размера всех чисел в файле
    if (size_to_map % sizeof(NumberType) != 0){
        throw std::length_error("Bad size_to_map: contains malformed NumberType");
    }

    int fd = open(filename.c_str(), O_RDWR);

    if (fd == -1){
        throw std::ios_base::failure("Error while opening " + filename);
    }

    // Маппинг части файла в память 
    this->file_contents = static_cast<NumberType*>(
                          mmap(nullptr,
                               size_to_map,
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED,
                               fd,
                               offset));


    if(this->file_contents == MAP_FAILED){
        throw std::runtime_error("Failed to map file"); 
    }
    
    this->count = size_to_map/sizeof(NumberType);

    // mmap после инициализации не зависит от дескриптора.
    // Дескриптор можно закрыть
    close(fd);
}

SortContainer::~SortContainer(){
    munmap(this->file_contents, this->count * sizeof(NumberType));
}


void SortContainer::Sort(OrderBy order){

    // qsort из cstdlib не может принять лямбду
    // а получение функции из лямбды я счел менее информативным, и даже бы сказал
    // запутывающим.
    // Поэтому было решено обойтись такой конструкцией
    struct Func{
        static int Asc(const void* left, const void* right){
            const NumberType l = *(static_cast<const NumberType*>(left));
            const NumberType r = *(static_cast<const NumberType*>(right));

            if( l < r ){
                return -1;
            }
            else if( l > r ){
                return 1;
            }
            else{
                return 0;
            }
        }
        static int Desc(const void* left, const void* right){
            const NumberType l = *(static_cast<const NumberType*>(left));
            const NumberType r = *(static_cast<const NumberType*>(right));
            
            if( l < r ){
                return 1;
            }
            else if( l > r ){
                return -1;
            }
            else{
                return 0;
            }
        }
    };
    switch(order){
        case OrderBy::Asc:
            std::qsort(this->file_contents, 
                       this->count,
                       sizeof(NumberType),
                       Func::Asc);
            break;
        case OrderBy::Desc:
            std::qsort(this->file_contents, 
                       this->count,
                       sizeof(NumberType),
                       Func::Desc);
            break;
    }
    
}







