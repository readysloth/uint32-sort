#include <iostream>
#include "file_manager.hpp"

int main(){
    // CopyFile("0.garbage","copied.garbage");
    
    FileManager file("0.garbage","copied.garbage");
    
    file.SortFile(OrderBy::Asc);

}
