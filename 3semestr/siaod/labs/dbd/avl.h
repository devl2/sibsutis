#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <list>

struct treeAVL {
    int data;
    short int balance = 0;
    treeAVL *L = nullptr;
    treeAVL *R = nullptr;
};

void rotateLL(treeAVL *&p) {
    treeAVL *q = p->L;
    p->balance = 0;
    q->balance = 0;
    p->L = q->R;
    q->R = p;
    p = q;
}

void rotateRR(treeAVL *&p) {
    treeAVL *q = p->R;
    p->balance = 0;
    q->balance = 0;
    p->R = q->L;
    q->L = p;
    p = q;
}

void rotateLR(treeAVL *&p) {
    treeAVL *q = p->L;
    treeAVL *r = q->R;
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

void rotateRL(treeAVL *&p) {
    treeAVL *q = p->R;
    treeAVL *r = q->L;
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

bool addAVL(treeAVL *&p, int data, bool &rost) {
    if (p == nullptr) {
        p = new treeAVL;
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

void rotateLL1(treeAVL *&p, bool &umen) {
    treeAVL *q = p->L;
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

void rotateRR1(treeAVL *&p, bool &umen) {
    treeAVL *q = p->R;
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

void BL(treeAVL *&p, bool &umen) {
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

void BR(treeAVL *&p, bool &umen) {
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

void del(treeAVL *&r, treeAVL *&q, bool &umen) {
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

bool deleteVertexWithKey(treeAVL *&p, int x, bool &umen) {
    treeAVL *q = nullptr;
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

void tprint1(treeAVL* p) {
    if (p == nullptr) return;
    std::cout << p->data << " ";
    tprint1(p->L);
    tprint1(p->R);
}

void tprint2(treeAVL *p) {
    if (p == nullptr) return;
    tprint2(p->L);
    std::cout << p->data << " ";
    tprint2(p->R);
}

int tsize(treeAVL* p) {
    if (p == nullptr) return 0;
    return 1 + tsize(p->L) + tsize(p->R);
}

int tsum(treeAVL* p) {
    if (p == nullptr) return 0;
    return p->data + tsum(p->L) + tsum(p->R);
}

int theight(treeAVL* p) {
    if (p == nullptr) return 0;
    return 1 + std::max(theight(p->L), theight(p->R));
}

double sdp(treeAVL* p, int l) {
    if (p == nullptr) return 0;
    return l + sdp(p->L, l + 1) + sdp(p->R, l + 1);
}

double avgHeight(treeAVL* p) {
    return sdp(p, 1) / tsize(p);
}



