#include <fstream>
#include <stdexcept>
#include <system_error>
#include <ios>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <uinistd.h>

#include "sort_container.hpp"

void CopyFile(std::string from_name, std::string to_name){
    std::ifstream  src(from_name, std::ios::binary);
    std::ofstream  dst(to_name,   std::ios::binary);

    dst << src.rdbuf();
}

SortContainer::Swap(&uint32_t l, &uint32_t r){
    l ^= r;
    r ^= l;
    l ^= r;
}

SortContainer::SortContainer(std::string filename, size_t size_to_map, off_t offset){
    if (size_to_map % sizeof(uint32_t) != 0){
        throw std::length_error("Bad size_to_map: contains malformed uint32_t");
    }

    int fd = open(filename.c_str(), O_RDONLY);

    if (fd == -1){
        throw std::ios_base::failure("Error while opening " + filename);
    }

    this.file_contents = mmap(NULL,
                              size_to_map,
                              PROT_READ | PROT_WRITE,
                              MAP_PRIVATE,
                              fd,
                              offset);

    if(this.file_contents == MAP_FAILED){
        throw std::system_error("Failed to map file"); 
    }

    this.count = size_to_map/sizeof(uint32_t);
    close(fd);
}

SortContainer::~SortContainer(){
    munmap(this.file_contents, this.count * sizeof(uint32_t));
}


SortContainer::MergeSort(){
    

}

















