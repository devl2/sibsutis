#include <iostream>

class List {
protected:
    int* array;
    int size;
    int count;
    static int objectCount; 

public:
    List() : array(nullptr), size(0), count(0) { ++objectCount; }

    List(int s) : size(s), array(new int[s]), count(0) {
        ++objectCount;
        for (int i = 0; i < size; ++i) {
            array[i] = 0; 
        }
    }

    virtual ~List() {
        delete[] array;
        --objectCount;
    }

    static int getObjectCount() { 
        return objectCount;
    }

    virtual void display() const {
        for (int i = 0; i < count; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};

int List::objectCount = 0;

class Stack : public List {
public:
    Stack(int s) : List(s) {}

    void push(int value) {
        if (count >= size) {
            throw std::overflow_error("Stack overflow.");
        }
        array[count++] = value;
    }

    int pop() {
        if (count == 0) {
            throw std::underflow_error("Stack underflow.");
        }
        return array[--count];
    }

    void display() const override {
        std::cout << "Stack: ";
        List::display();
    }
};

class Queue : public List {
private:
    int front;  
    int rear;  

public:
    Queue(int s) : List(s), front(0), rear(0) {}

    void enqueue(int value) {
        if (rear >= size) {
            throw std::overflow_error("Queue overflow.");
        }
        array[rear++] = value;
        count++;
    }

    int dequeue() {
        if (front == rear) {
            throw std::underflow_error("Queue underflow.");
        }
        count--;
        return array[front++];
    }

    void display() const override {
        std::cout << "Queue: ";
        for (int i = front; i < rear; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    try {
        Stack stack(5);
        stack.push(1);
        stack.push(2);
        stack.push(5);
        stack.push(4);
        stack.pop();
        stack.display();

        Queue queue(5);
        queue.enqueue(3);
        queue.enqueue(4);
        queue.enqueue(7);
        queue.dequeue();
        queue.display();

        std::cout << "Number of List objects: " << List::getObjectCount() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
