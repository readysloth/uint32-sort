#include <iostream>
#include "sort_container.hpp"

int main(){
    CopyFile("0.garbage","copied.garbage");
    
    SortContainer("copied.garbage", 1024, 0).Sort(OrderBy::Asc);
    

}
