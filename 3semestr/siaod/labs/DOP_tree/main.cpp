#include "pr_alg.h"
#include "t_alg.h"

int main(){
    while (true){
        std::cout << std::endl;
        std::cout << "1.Print DOP tree" << std::endl;
        std::cout << "2.Print tree with A1 and A2 alg" << std::endl;
        std::cout << "3.Exit" << std::endl;
        int x;
        std::cout << "enter num:";
        std::cin >> x;
        switch(x){
            case 1:{
                t_DOP();
                break;
            } case 2:{
                pr_DOP();
                break;
            } case 3:{
                return 0;
            } default: {
                std::cout << "Wrong!";
            }
        }
    }
    return 0;
}