#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <list>

struct tree {
    int data;
    short int balance = 0;
    tree *L = nullptr;
    tree *R = nullptr;
};

void rotateLL(tree *&p) {
    tree *q = p->L;
    p->balance = 0;
    q->balance = 0;
    p->L = q->R;
    q->R = p;
    p = q;
}

void rotateRR(tree *&p) {
    tree *q = p->R;
    p->balance = 0;
    q->balance = 0;
    p->R = q->L;
    q->L = p;
    p = q;
}

void rotateLR(tree *&p) {
    tree *q = p->L;
    tree *r = q->R;
    if (r->balance < 0) p->balance = 1;
    else p->balance = 0;

    if (r->balance > 0) q->balance = -1;
    else q->balance = 0;

    r->balance = 0;
    q->R = r->L;
    p->L = r->R;
    r->L = q;
    r->R = p;
    p = r;
}

void rotateRL(tree *&p) {
    tree *q = p->R;
    tree *r = q->L;
    if (r->balance > 0) p->balance = -1;
    else p->balance = 0;

    if (r->balance < 0) q->balance = 1;
    else q->balance = 0;

    r->balance = 0;
    q->L = r->R;
    p->R = r->L;
    r->R = q;
    r->L = p;
    p = r;
}

bool addAVL(tree *&p, int data, bool &rost) {
    if (p == nullptr) {
        p = new tree;
        p->data = data;
        rost = true;
    } else if (p->data > data) {
        if (addAVL(p->L, data, rost)) {
            if (rost) {
                if (p->balance > 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = -1;
                    rost = true;
                } else if (p->L->balance < 0) {
                    rotateLL(p);
                    rost = false;
                } else {
                    rotateLR(p);
                    rost = false;
                }
            }
        } else {
            return false;
        }
    } else if (p->data < data) {
        if (addAVL(p->R, data, rost)) {
            if (rost) {
                if (p->balance < 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = 1;
                    rost = true;
                } else if (p->R->balance > 0) {
                    rotateRR(p);
                    rost = false;
                } else {
                    rotateRL(p);
                    rost = false;
                }
            }
        } else {
            return false;
        }
    } else {
        return false; 
    }
    return true;
}

void rotateLL1(tree *&p, bool &umen) {
    tree *q = p->L;
    if (q->balance == 0) {
        q->balance = 1;
        p->balance = -1;
        umen = false;
    } else {
        q->balance = 0;
        p->balance = 0;
    }
    p->L = q->R;
    q->R = p;
    p = q;
}

void rotateRR1(tree *&p, bool &umen) {
    tree *q = p->R;
    if (q->balance == 0) {
        p->balance = 1;
        q->balance = -1;
        umen = false;
    } else {
        p->balance = 0;
        q->balance = 0;
    }
    p->R = q->L;
    q->L = p;
    p = q;
}

void BL(tree *&p, bool &umen) {
    if (p->balance == -1) {
        p->balance = 0;
    } else if (p->balance == 0) {
        p->balance = 1;
        umen = false;
    } else if (p->balance == 1) {
        if (p->R->balance >= 0) {
            rotateRR1(p, umen);
        } else {
            rotateRL(p);
        }
    }
}

void BR(tree *&p, bool &umen) {
    if (p->balance == 1) {
        p->balance = 0;
    } else if (p->balance == 0) {
        p->balance = -1;
        umen = false;
    } else if (p->balance == -1) {
        if (p->R->balance <= 0) {
            rotateLL1(p, umen);
        } else {
            rotateLR(p);
        }
    }
}

void del(tree *&r, tree *&q, bool &umen) {
    if (r->R != nullptr) {
        del(r->R, q, umen);
        if (umen) {
            BR(r, umen);
        }
    } else {
        q->data = r->data;
        q = r;
        r = r->L;
        umen = true;
    }
}

bool deleteVertexWithKey(tree *&p, int x, bool &umen) {
    tree *q = nullptr;
    if (p == nullptr)
        return 1;
    else if (p->data > x) {
        if (deleteVertexWithKey(p->L, x, umen))
            return 1;
        if (umen)
            BL(p, umen);
    } else if (p->data < x) {
        if (deleteVertexWithKey(p->R, x, umen))
            return 1;
        if (umen)
            BR(p, umen);
    } else {
        q = p;
        if (q->R == nullptr) {
            p = q->L;
            umen = true;
        } else if (q->L == nullptr) {
            p = q->R;
            umen = true;
        } else {
            del(q->L, q, umen);
            if (umen)
                BL(p, umen);
        }
        delete q;
    }
    return 0;
}

void tprint2(tree *p) {
    if (p == nullptr) return;
    tprint2(p->L);
    std::cout << p->data << " ";
    tprint2(p->R);
}

int main() {
    srand(time(nullptr));
    const int size = 10;

    int A[size];
    for (int i = 0; i < size; i++) {
        A[i] = rand() % 100;
    }

    tree *avl = nullptr;
    bool umen;
    for (int i = 0; i < size; ++i) {
        umen = false;
        addAVL(avl, A[i], umen);
    }

    std::cout << "\nОбход слева направо (AVL): ";
    tprint2(avl);
    std::cout << std::endl;

    for (int i = 0; i < 10; ++i) {
        int x;
        std::cout << "Введите значение для удаления (" << i + 1 << "/10): ";
        std::cin >> x;

        if (!deleteVertexWithKey(avl, x, umen)) {  // Условие на успешное удаление
        std::cout << "Дерево после удаления " << x << ": ";
        } else {
            std::cout << "Значение " << x << " не найдено для удаления." << std::endl;
        }

        tprint2(avl);
        std::cout << std::endl;
    }

    return 0;
}
