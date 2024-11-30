#include "avl.h"
#include "dbd.h"
#include <set>

int main() {
   srand((time(nullptr)));

    const int size = 100;
    std::set<int> unique_values;

    while (unique_values.size() < size) {
        int D = rand() % 1000;
        unique_values.insert(D); 
    }

    int A[size];
    int index = 0;

    for (const int& value : unique_values) {
        A[index++] = value;
    }

    treeAVL* avl = nullptr;
    tree* dbd = nullptr;
    bool umen, VR, HR;

    for (int i = 0; i < size; ++i) {
        umen = false;
        addAVL(avl, A[i], umen);
        B2INSERT(dbd, A[i], VR, HR);
    }

    std::cout << "\nAVL: ";
    tprint1(avl);
    std::cout << std::endl;

    std::cout << "\nAVL: ";
    tprint2(avl);
    std::cout << std::endl;

    std::cout << "\nDBD: ";
    tprint1(dbd);
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "DBD: ";
    tprint2(dbd);
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << " n = 100 |" << " Размер  |" << " Контр. сумма   |" << " Высота   |" << " Средн. высота |" << std::endl;
    std::cout << "  АВЛ    |" << tsize(avl) << "      |" << tsum(avl) << "           |" << theight(avl) << "         |" << avgHeight(avl) << "            |" << std::endl;
    std::cout << "  ДБД    |" << tsize(dbd) << "      |" << tsum(dbd) << "           |" << theight(dbd) << "         |" << avgHeight(dbd) << "           |" << std::endl;

    return 0;
}
