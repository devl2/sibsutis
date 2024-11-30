#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <list>

struct tree {
    int data;
    bool balance = false;
    tree *L = nullptr;
    tree *R = nullptr;
};

void tprint1(tree* p) {
    if (p == nullptr) return;
    std::cout << p->data << " ";
    tprint1(p->L);
    tprint1(p->R);
}

void tprint2(tree *p) {
    if (p == nullptr) return;
    tprint2(p->L);
    std::cout << p->data << " ";
    tprint2(p->R);
}

bool B2INSERT(tree*& p, int data, bool &VR, bool &HR){
    if(p == nullptr){
        p = new tree;
        p->data = data;
        p->L = p->R = nullptr;
        p->balance = false;
        VR = true;
    }
    else if (p->data > data){
        if(B2INSERT(p->L, data, VR, HR)){
            if(VR){
                if(p->balance=0){
                    tree *q = p->L;
                    p->L = q->R;
                    q->R = p;
                    p = q;
                    q->balance = true;
                    VR = false;
                    HR = true;
                } else{
                    p->balance = false;
                    VR = true;
                    HR = false;
                }
            }
            else 
                HR = false;
        }
        else
            return false;
    }
    else if (p->data < data){
        if(B2INSERT(p->R, data, VR, HR)){
            if(VR){
                p->balance = true;
                HR = true;
                VR = false;
            } else if(HR){
                if (p->balance){
                    tree * q = p->R;
                    p->balance = false;
                    q->balance = false;
                    p->R = q->L;
                    q->L = p;
                    p = q;
                    VR = true;
                    HR = false;
                }
                else
                    HR = false;
            }
        }
        else
            return false;
    }
    else
        return false;
    return true;
}

int tsize(tree* p) {
    if (p == nullptr) return 0;
    return 1 + tsize(p->L) + tsize(p->R);
}

int tsum(tree* p) {
    if (p == nullptr) return 0;
    return p->data + tsum(p->L) + tsum(p->R);
}

int theight(tree* p) {
    if (p == nullptr) return 0;
    return 1 + std::max(theight(p->L), theight(p->R));
}

double sdp(tree* p, int l) {
    if (p == nullptr) return 0;
    return l + sdp(p->L, l + 1) + sdp(p->R, l + 1);
}

double avgHeight(tree* p) {
    return sdp(p, 1) / tsize(p);
}