#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iomanip>
#include <cstring>
#include <cstdio>


const int MAX_RECORDS = 4000;

using namespace std;

struct record {
    char name[32];
    char street[18];
    short int house;
    short int apartment;
    char date[10];
};

struct Node {
    record data;
    Node* next;
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() : head(nullptr) {}

    void add_record(const record& rec) {
        Node* newNode = new Node{ rec, nullptr };
        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void clear() {
        Node* temp = head;
        while (temp) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }

    Node* get_head() const { return head; }
    
    int size() const {
        int count = 0;
        Node* current = head;
        while (current) {
            count++;
            current = current->next;
        }
        return count;
    }

    void display_records(int start, int pageSize) const {
        Node* current = head;
        for (int i = 0; i < start && current; ++i) {
            current = current->next;
        }
        for (int i = 0; i < pageSize && current; ++i) {
            cout << current->data.name << " "
                 << current->data.street << " "
                 << current->data.house << " "
                 << current->data.apartment << " "
                 << current->data.date << endl;
            current = current->next;
        }
    }
};

class Queue {
private:
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    void add_to_queue(const record& rec) {
        Node* newQueueNode = new Node{rec, nullptr};
        if (!rear) {
            rear = newQueueNode;
            front = rear;
        } else {
            rear->next = newQueueNode;
            rear = newQueueNode;
        }
    }

    void printQueue() const {
        int i = 0;
        Node* temp = front;
        while (temp) {
            cout << i + 1 << " " << temp->data.name << " " 
                 << temp->data.street << " " << temp->data.house << " "
                 << temp->data.apartment << " " << temp->data.date << endl;
            temp = temp->next;
            ++i;
        }
    }

    void clear_queue() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

struct TreeNode {
    record data;       // Store the record data
    int num;            // Some identifier (optional)
    int weight;         // Some weight (optional)
    bool use;           // Flag to indicate if the node is used
    int index;          // An index (optional)
    TreeNode* left = nullptr;  // Left child
    TreeNode* right = nullptr;  // Right child
    TreeNode* middle = nullptr;  // Middle child for duplicates (optional)
};

LinkedList load_data(int size) {
    FILE* file = fopen("C:/sibsutis/kurs(ne robit)/testBase4.dat", "rb");
    LinkedList records;
    record rec;
    for (int i = 0; i < size; i++) {
        if (fread(&rec, sizeof(record), 1, file) != 1) {
            break;
        }
        records.add_record(rec);
    }
    fclose(file);
    return records;
}

void DigitalSortStreet(LinkedList& records) {
    const int BYTE_RANGE = 256;
    LinkedList queues[BYTE_RANGE];
    Node* current = records.get_head();

    for (int i = 0; i < BYTE_RANGE; i++) {
        queues[i].clear();
    }

    for (int byteIndex = 0; byteIndex < sizeof(short); byteIndex++) {
        current = records.get_head();
        while (current) {
            unsigned short digit = ((unsigned short)current->data.street[0] >> (byteIndex * 8)) & 0xFF;
            queues[digit].add_record(current->data);
            current = current->next;
        }

        records.clear();
        for (int i = 0; i < BYTE_RANGE; i++) {
            Node* queueHead = queues[i].get_head();
            while (queueHead) {
                records.add_record(queueHead->data);
                queueHead = queueHead->next;
            }
        }
    }
}

void DigitalSorthouse(LinkedList& records) {
    const int BYTE_RANGE = 256;
    LinkedList queues[BYTE_RANGE];
    Node* current = records.get_head();

    for (int i = 0; i < BYTE_RANGE; i++) {
        queues[i].clear();
    }

    for (int byteIndex = 0; byteIndex < sizeof(short); byteIndex++) {
        current = records.get_head();
        while (current) {
            unsigned char digit = ((unsigned short)current->data.house >> (byteIndex * 8)) & 0xFF;
            queues[digit].add_record(current->data);
            current = current->next;
        }

        records.clear();
        for (int i = 0; i < BYTE_RANGE; i++) {
            Node* queueHead = queues[i].get_head();
            while (queueHead) {
                records.add_record(queueHead->data);
                queueHead = queueHead->next;
            }
        }
    }
}

void binarySearch(LinkedList& records) {
    int x, L = 0, R = records.size() - 1;
    record* array = new record[records.size()];
    Queue queue;

    Node* current = records.get_head();
    cout << "Enter house number: ";
    cin >> x;

    for (int i = 0; i < records.size(); i++) {
        array[i] = current->data;
        current = current->next;
    }

    while (L <= R) {
        int m = (L + R) / 2;
        if (array[m].house < x) {
            L = m + 1;
        } else {
            R = m - 1;
        }
    }

    for (int i = L; i < records.size() && array[i].house == x; i++) {
        queue.add_to_queue(array[i]);
    }

    queue.printQueue();
    delete[] array;
}

void addTreeNode(TreeNode*& root, const record& rec, int weight) 
{
    if (!root) {
        root = new TreeNode();
        root->data = rec;
        root->weight = weight;
        root->use = true;  // Mark the node as "used"
    } else if (strcmp(rec.name, root->data.name) < 0) {
        addTreeNode(root->left, rec, weight);
    } else if (strcmp(rec.name, root->data.name) > 0) {
        addTreeNode(root->right, rec, weight);
    } else {
        if (root->middle == nullptr) {
            root->middle = new TreeNode();
            root->middle->data = rec;
            root->middle->weight = weight;
            root->middle->use = true;
        } else {
            addTreeNode(root->middle, rec, weight);
        }
    }
}

void print_tree(TreeNode* root) {
    if (root) {
        print_tree(root->left);
        cout << setw(5) << root->num << " | "
             << root->data.name << " | "
             << root->data.street << " | "
             << root->data.house << " | "
             << setw(3) << root->data.apartment << " | "
             << root->data.date << "| "
             << setw(4) << root->weight << " |" << endl;
        print_tree(root->right);
    }
}

void searchByApartment(TreeNode* root, int apartmentNumber) {
    if (root == nullptr) return;
    searchByApartment(root->left, apartmentNumber);
    if (root->data.apartment == apartmentNumber) {
        cout << setw(5) << root->num << " | "
             << root->data.name << " | "
             << root->data.street << " | "
             << root->data.house << " | "
             << setw(3) << root->data.apartment << " | "
             << root->data.date << "| "
             << setw(4) << root->weight << " |" << endl;
    }
    searchByApartment(root->right, apartmentNumber);
}

int main_menu(LinkedList& records) {
    LinkedList sortedRecords;
    TreeNode* root = nullptr;
    
    while (true) {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Display Source Data\n";
        std::cout << "2. Sort Data\n";
        std::cout << "3. Search Records\n";
        std::cout << "4. Create and Print Optimal Search Tree\n";
        std::cout << "5. Exit\n";
        std::cout << "===================\n";
        std::cout << "Please choose an option (1-5): ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                int pageSize = 20;
                int currentPage = 0;
                while (true) {
                    records.display_records(currentPage * pageSize, pageSize);
                    std::cout << "Press 'q' to return to main menu or 'n' for next page: ";
                    char pageChoice;
                    std::cin >> pageChoice;
                    if (pageChoice == 'q') break;
                    else if (pageChoice == 'n') currentPage++;
                    else std::cout << "Invalid choice, please press 'q' or 'n'." << std::endl;
                }
                break;
            }

            case 2: {
                sortedRecords.clear();
                Node* current = records.get_head();
                while (current) {
                    sortedRecords.add_record(current->data);
                    current = current->next;
                }

                DigitalSortStreet(sortedRecords);
                DigitalSorthouse(sortedRecords);
                std::cout << "Records sorted." << std::endl;

                int pageSize = 20;
                int currentPage = 0;
                int totalRecords = sortedRecords.size();
                
                while (true) {
                    std::cout << "\nPage " << (currentPage + 1) << ":\n";
                    sortedRecords.display_records(currentPage * pageSize, pageSize);
                    std::cout << "Press 'n' for next page, 'q' to exit: ";
                    
                    char pageChoice;
                    std::cin >> pageChoice;
                    
                    if (pageChoice == 'n') {
                        if ((currentPage + 1) * pageSize < totalRecords) {
                            currentPage++;
                        } else {
                            std::cout << "No more records." << std::endl;
                        }
                    } else if (pageChoice == 'q') {
                        currentPage = 0;
                        break;
                    } else {
                        std::cout << "Error! Please type 'n' or 'q'." << std::endl;
                    }
                }
                break;
            }

            case 3: {
                binarySearch(sortedRecords);
                break;
            }

            case 4: {
                int size = sortedRecords.size();
                TreeNode** treeNodes = new TreeNode*[size];
                Node* current = sortedRecords.get_head();
                for (int i = 0; i < size; i++) {
                    treeNodes[i] = new TreeNode();
                    treeNodes[i]->data = current->data;
                    current = current->next;
                }

                // Implement the calculation of the optimal search tree here
                // Example: A2(root, treeNodes, 0, size-1);
                
                std::cout << "Optimal search tree created." << std::endl;
                print_tree(root);
                break;
            }

            case 5: {
                std::cout << "Exiting the menu." << std::endl;
                return 0;
            }

            default:
                std::cout << "Invalid choice! Please choose a number between 1 and 5." << std::endl;
                break;
        }
    }
}

#include "menu.h"

int main() {
	SetConsoleCP(866);
    SetConsoleOutputCP(866);

    List records = data(MAX_RECORDS);
    tree* root = nullptr;
    menu(records);
    return 0;
}
