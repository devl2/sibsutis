#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>

struct tnode {
    int data;
    tnode* left;
    tnode* right;
};

tnode* sdp_tree_recursive(tnode* root, int D) {
    if (root == nullptr) {
        tnode* newNode = new tnode;
        newNode->data = D;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    
    if (D < root->data) {
        root->left = sdp_tree_recursive(root->left, D);
    } else if (D > root->data) {
        root->right = sdp_tree_recursive(root->right, D);
    }
    
    return root;
}

tnode* sdp_tree_pointer(tnode* root, int D) {
    tnode **p = &root;
    while (*p != nullptr) {
        if (D < (*p)->data) {
            p = &((*p)->left);
        } else if (D > (*p)->data) {
            p = &((*p)->right);
        } else {
            return root;
        }
    }

    *p = new tnode; 
    (*p)->data = D; 
    (*p)->left = nullptr;
    (*p)->right = nullptr;
    return root; 
}

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

void tprint(tnode* p) {
    if (p == nullptr) return;
    std::cout << p->data << " ";
    tprint(p->left);
    tprint(p->right);
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


void delete_tree(tnode* p) {
    if (p == nullptr) return;
    delete_tree(p->left);
    delete_tree(p->right);
    delete p;
}

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

    tnode* random_tree_recursive = nullptr;
    tnode* random_tree_pointer = nullptr;

    for (int i = 0; i < size; ++i) {
        random_tree_recursive = sdp_tree_recursive(random_tree_recursive, A[i]);
        random_tree_pointer = sdp_tree_pointer(random_tree_pointer, A[i]);
    }

    std::sort(A, A + size);
    tnode* balanced_tree = isdp_tree(A, 0, size - 1);

    std::cout << "\nСлучайное дерево (с рекурсией): ";
    tprint(random_tree_recursive);
    std::cout << std::endl;

    std::cout << "Случайное дерево (с указателями): ";
    tprint(random_tree_pointer);
    std::cout << std::endl;

    std::cout << "Сбалансированное дерево: ";
    tprint(balanced_tree);
    std::cout << std::endl;

    std::cout << " n = 100 |" << " Размер  |" << " Контр. сумма   |" << " Высота   |" << " Средн. высота |" << std::endl;
    std::cout << "  ИСДП   |" << tsize(balanced_tree) << "      |" << tsum(balanced_tree) << "           |" << theight(balanced_tree) << "         |" << avgHeight(balanced_tree) << "            |" << std::endl;
    std::cout << "  СДП1   |" << tsize(random_tree_recursive) << "       |" << tsum(random_tree_recursive) << "           |" << theight(random_tree_recursive) << "        |" << avgHeight(random_tree_recursive) << "        |" << std::endl;
    std::cout << "  СДП2   |" << tsize(random_tree_pointer) << "       |" << tsum(random_tree_pointer) << "           |" << theight(random_tree_pointer) << "        |" << avgHeight(random_tree_pointer) << "        |" << std::endl;

    delete_tree(random_tree_recursive);
    delete_tree(random_tree_pointer);
    delete_tree(balanced_tree);

    return 0;
}
