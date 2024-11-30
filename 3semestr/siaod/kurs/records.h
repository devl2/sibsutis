#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <unordered_map>

const int MAX_RECORDS = 4000;

using namespace std;

struct record3 {
    char fio[32];
    char street[18];
    short int house;
    short int apart;
    char date[10];
};

struct Node {
    record3 rec;
    Node* next;
};

class List {
private:
    Node* head;
public:
    List() : head(nullptr) {}

    void push_back(const record3& rec) {
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
            cout << i + 1 << " " << current->rec.fio << " "
                 << current->rec.street << " "
                 << current->rec.house << " "
                 << current->rec.apart << " "
                 << current->rec.date << endl;
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

    // Добавление элемента в очередь
    void queue_add(const record3& rec) {
        Node* newQueueNode = new Node{rec, nullptr};
        if (!rear) {
            rear = newQueueNode;
            front = rear;
        } else {
            rear->next = newQueueNode;
            rear = newQueueNode;
        }
    }

    // Извлечение элемента из очереди (удаление с начала)
    record3 queue_pop() {
        if (front) {
            Node* temp = front;
            record3 rec = front->rec;
            front = front->next;
            if (!front) {
                rear = nullptr; // Если очередь опустела, rear тоже обнуляется
            }
            delete temp;
            return rec;
        }
        throw std::out_of_range("Queue is empty");  // Если очередь пуста, выбрасываем исключение
    }

    // Проверка на пустоту очереди
    bool is_empty() const {
        return front == nullptr;
    }

    // Печать содержимого очереди
    void printQueue() const {
        int i = 0;
        Node* temp = front;
        while (temp) {
            cout << i + 1 << " " << temp->rec.fio << " " 
                 << temp->rec.street << " " << temp->rec.house << " "
                 << temp->rec.apart << " " << temp->rec.date << endl;
            temp = temp->next;
            ++i;
        }
    }

    // Очистка очереди
    void queue_clear() {
        while (front) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        rear = nullptr;
    }
};

struct tree {
    record3 data;      
    int num;            
    int weight;         
    int index;    
    tree* L = nullptr;  
    tree* R = nullptr;  
    tree* M = nullptr;
};

struct chanceSymbol
{
    char symbol; // Символ
    unsigned int quantity; // Встречаемость в текте
    float probability; // Вероятность
    unsigned short int lengthCW; // Длина кодового слова
    char * codeword; // Кодовое слово
};

struct Gilbert
{
    unsigned char ch = 0;
    float Pi = 0;
    float Qi = 0;
    unsigned short int Li = 0;
    char *codeword = nullptr;
};

List data(int size) {
    FILE* base = fopen("D:/solutions/kurs(ne robit)/testBase4.dat", "rb");
    List records;
    record3 rec;
    int actualSize = 0;
    for (int i = 0; i < size; i++) {
        if (fread(&rec, sizeof(record3), 1, base) != 1) {
            break;
        }
        records.push_back(rec);
        actualSize++;
    }
    fclose(base);
    std::cout << "Actual records read: " << actualSize << std::endl;
    return records;
}

