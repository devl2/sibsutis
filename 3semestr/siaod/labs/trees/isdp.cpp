#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

struct tnode {
    int data;
    tnode* left;
    tnode* right;
};

tnode* isdp_tree(int* A, int L, int R) {
    if (L > R) {
        return nullptr;
    }

    int m = (L + R) / 2;
    tnode* p = new tnode; 
    p->data = A[m];
    p->left = isdp_tree(A, L, m - 1); 
    p->right = isdp_tree(A, m + 1, R); 
    return p; 
}

void tprint1(tnode* p) {
    if (p == nullptr) return;
    std::cout << p->data << " ";
    tprint1(p->left);
    tprint1(p->right);
}

void tprint2(tnode* p) {
    if (p == nullptr) return;
    tprint2(p->left);
    std::cout << p->data << " ";
    tprint2(p->right);
}

int tsize(tnode* p) {
    if (p == nullptr) return 0;
    return 1 + tsize(p->left) + tsize(p->right);
}

int tsum(tnode* p) {
    if (p == nullptr) return 0;
    return p->data + tsum(p->left) + tsum(p->right);
}

int theight(tnode* p) {
    if (p == nullptr) return 0;
    return 1 + std::max(theight(p->left), theight(p->right));
}

double sdp(tnode* p, int l) {
    if (p == nullptr) return 0;
    return l + sdp(p->left, l + 1) + sdp(p->right, l + 1);
}

double avgHeight(tnode* p) {
    return sdp(p, 1) / tsize(p);
}

int main() {
    srand((time(nullptr)));
    
    const int size = 100;
    int A[size];

    for (int i = 0; i < size; ++i) {
        A[i] = rand() % 1000;
    }

    std::cout << "исходный массив: ";
    for (int i = 0; i < size; ++i) {
        std::cout << A[i] << " ";
    }

    std::sort(A, A + size);
    
    tnode* p = isdp_tree(A, 0, size - 1);
    
    std::cout << std::endl;
    std::cout << "\nисходный массив(отсортированный): ";
    for (int i = 0; i < size; ++i) {
        std::cout << A[i] << " ";
    }
    
    std::cout << std::endl;
    std::cout << "\nобход в симметричном порядке: ";
    tprint2(p);
    std::cout << std::endl;
    
    std::cout << std::endl;
    std::cout << "размер: " << tsize(p) << std::endl;
    std::cout << "сумма: " << tsum(p) << std::endl;
    std::cout << "высота: " << theight(p) << std::endl;
    std::cout << "средняя высота: " << std::fixed << std::setprecision(2) << avgHeight(p) << std::endl;

    return 0;
}
