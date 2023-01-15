#include "main.hpp"

int main(){
    init();

    return 0;
}

void init(){
    for (int i = 1; i <= width; i++){
        std::cout << wall;
    }
    std::cout << std::endl;
    for (int i = 2; i <= height - 1; i++){
        for (int i = 1; i <= width; i++){
            if (i == 1 || i == width){
                std::cout << wall;
            }
            else{
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    for (int i = 1; i <= width; i++){
        std::cout << wall;
    }
    std::cout << std::endl; 
}