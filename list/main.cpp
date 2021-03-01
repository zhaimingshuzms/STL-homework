#include <iostream>
#include "list.hpp"
int main() {
    sjtu::list<int> l;
    for (sjtu::list<int>::iterator it=l.head(); it.available(); ++it){
        std::cout<<(*it)<<std::endl;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
