#include "records.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;

void DigitalSortStreetAndHouse(List& records) {
    const int BYTE_RANGE = 256;
    List queues[BYTE_RANGE];

    for (int byteIndex = 0; byteIndex < sizeof(short); byteIndex++) {
        Node* current = records.get_head();
        
        while (current) {
            unsigned char digit = ((unsigned short)current->rec.house >> (byteIndex * 8)) & 0xFF;
            queues[digit].push_back(current->rec);
            current = current->next;
        }

        records.clear();
        for (int i = 0; i < BYTE_RANGE; i++) {
            Node* queueHead = queues[i].get_head();
            while (queueHead) {
                records.push_back(queueHead->rec);
                queueHead = queueHead->next;
            }
            queues[i].clear();
        }
    }

    for (int charIndex = 2; charIndex >= 0; charIndex--) {
        Node* current = records.get_head();

        while (current) {
            unsigned char digit = 0;
            if (charIndex < strlen(current->rec.street)) {
                digit = (unsigned char)current->rec.street[charIndex];
            }
            queues[digit].push_back(current->rec);
            current = current->next;
        }

        records.clear();
        for (int i = 0; i < BYTE_RANGE; i++) {
            Node* queueHead = queues[i].get_head();
            while (queueHead) {
                records.push_back(queueHead->rec);
                queueHead = queueHead->next;
            }
            queues[i].clear();
        }
    }
}

void addTree(tree*& root, record3 data, int weight) {
    if (!root) {
        root = new tree();
        root->data = data;
        root->weight = weight;
        root->L = root->R = nullptr;
        return;
    }

    if (data.apart < root->data.apart) {
        addTree(root->L, data, weight);
    } else {
        addTree(root->R, data, weight);
    }
}


void binarySearch(List& records, Queue& foundRecords, const char* prefix) {
    int L = 0, R = records.size() - 1;
    record3* a = new record3[records.size()];

    Node* flag = records.get_head();
    for (int i = 0; i < records.size(); i++) {
        a[i] = flag->rec;
        flag = flag->next;
    }

    bool found = false;
    while (L <= R) {
        int m = (L + R) / 2;

        if (strncmp(a[m].street, prefix, 3) < 0) {
            L = m + 1;
        } else if (strncmp(a[m].street, prefix, 3) > 0) {
            R = m - 1;
        } else {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Records found:\n";
        for (int i = 0; i < records.size(); i++) {
            if (strncmp(a[i].street, prefix, 3) == 0) {
                foundRecords.queue_add(a[i]);
            }
        }

        foundRecords.printQueue();

    } else {
        cout << "No records found." << endl;
    }

    delete[] a;
}

void A2(tree*& root, tree* arr[], int left, int right) {
    if (left > right) return;

    int totalWeight = 0, sum = 0;

    for (int j = left; j <= right; ++j) {
        totalWeight += arr[j]->weight;
    }

    int i = left;
    while (i <= right && sum + arr[i]->weight < totalWeight / 2) {
        sum += arr[i]->weight;
        ++i;
    }

    if (i > right) i = right;

    addTree(root, arr[i]->data, arr[i]->weight);

    A2(root, arr, left, i - 1);
    A2(root, arr, i + 1, right);
}


void print(tree* root, int& i) {
    if (!root) return;

    print(root->L, i);
    cout << setw(5) << i + 1 << " "
         << root->data.fio << "  "
         << root->data.street << "  "
         << root->data.house << "  "
         << setw(3) << root->data.apart << "  "
         << root->data.date << " "
         << setw(4) << root->weight << " " << endl;
    i++;
    print(root->R, i);
}

void createOptimalSearchTree(tree*& root, Queue& foundRecords) {
    if (foundRecords.is_empty()) {
        cout << "No records to create a tree." << endl;
        return;
    }

    tree* arr[MAX_RECORDS];
    int count = 0;

    while (!foundRecords.is_empty() && count < MAX_RECORDS) {
        arr[count] = new tree();
        record3 rec = foundRecords.queue_pop();
        arr[count]->data = rec;
        arr[count]->weight = count;
        arr[count]->L = arr[count]->R = nullptr;
        count++;
    }

    A2(root, arr, 0, count - 1);

    int index = 0;
    std::cout << "\n=== Optimal Search Tree ===\n";
    print(root, index);

    for (int i = 0; i < count; ++i) {
        delete arr[i];
    }
}

void bSearchInTree(tree* root, int h, int& i) {
    if (!root) return;

    if (root->data.apart == h) {
        cout << setw(5) << i + 1 << " "
             << root->data.fio << "  "
             << root->data.street << "  "
             << root->data.house << "  "
             << setw(3) << root->data.apart << "  "
             << root->data.date << "  "
             << setw(4) << root->weight << " " << endl;
        i++;
        }

    bSearchInTree(root->L, h, i);
    bSearchInTree(root->R, h, i);
}

void searchInTree(tree* root) {
    char prefix[4];
    int h;
    int index = 0;
    cout << "Enter apart num: ";
    cin >> h;
    
    bSearchInTree(root, h, index);
}

void clearTree(tree*& root) {
    if (!root) return;

    clearTree(root->L);
    clearTree(root->M);
    clearTree(root->R);

    delete root;
    root = nullptr;
}
