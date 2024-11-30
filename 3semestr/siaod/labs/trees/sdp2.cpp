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

tnode* deleteNode(tnode* root, int D) {
    if (root == nullptr) return root;

    if (D < root->data) {
        root->left = deleteNode(root->left, D);
    } else if (D > root->data) {
        root->right = deleteNode(root->right, D);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }

        if (root->left == nullptr) {
            tnode* temp = root->right;
            delete root;
            return temp;
        }

        else if (root->right == nullptr) {
            tnode* temp = root->left;
            delete root;
            return temp;
        }

        tnode* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left; 
        }

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

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

void tprint2(tnode* p) {
    if (p == nullptr) return;
    tprint2(p->left);
    std::cout << p->data << " ";
    tprint2(p->right);
}

int main() {
    srand((time(nullptr)));

    const int size = 100;
    int A[size];
    int index = 0;

    while (index < size) {
        int D = rand() % 1000;
        A[index++] = D; 
    }

    tnode* random_tree_recursive = nullptr;
    for (int i = 0; i < size; ++i) {
        random_tree_recursive = sdp_tree_recursive(random_tree_recursive, A[i]);
    }

    std::cout << "Исходное дерево: ";
    tprint2(random_tree_recursive);
    std::cout << std::endl;

    for (int i = 0; i < 10; ++i) {
        int value_to_delete;
        std::cout << "Введите значение для удаления (" << i + 1 << "/10): ";
        std::cin >> value_to_delete;
        
        random_tree_recursive = deleteNode(random_tree_recursive, value_to_delete);

        std::cout << "Дерево после удаления " << value_to_delete << ": ";
        tprint2(random_tree_recursive);
        std::cout << std::endl;
    }

    return 0;
}
