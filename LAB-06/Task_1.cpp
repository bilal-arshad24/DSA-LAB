#include <iostream>
#include <string>
using namespace std;

// Base class for the queue.
template <typename T>
class Queue {
protected:
    T* arr;
    int maxSize;
    int currentSize;

public:
    Queue(int maxQueueSize) {
        maxSize = maxQueueSize;
        currentSize = 0;
        arr = new T[maxSize];
    }

    virtual void enqueue(T data) = 0;
    virtual T dequeue() = 0;
    virtual T peek() = 0;
    virtual bool isFull() = 0;
    virtual bool isEmpty() = 0;

    virtual ~Queue() {
        delete[] arr;
    }
};

// Circular queue class that reuses empty array positions.
template <typename T>
class MyQueue : public Queue<T> {
private:
    int front, rear;

public:
    MyQueue(int maxQueueSize) : Queue<T>(maxQueueSize) {
        front = 0;
        rear = -1;
    }

    bool isEmpty() override {
        return this->currentSize == 0;
    }

    bool isFull() override {
        return this->currentSize == this->maxSize;
    }

    void enqueue(T data) override {
        if (isFull()) {
            cout << "Queue is full. Cannot add more data.\n";
            return;
        }

        rear = (rear + 1) % this->maxSize;
        this->arr[rear] = data;
        this->currentSize++;
    }

    T dequeue() override {
        if (isEmpty()) {
            cout << "Queue is empty. No customer to serve.\n";
            return T();
        }

        T data = this->arr[front];
        front = (front + 1) % this->maxSize;
        this->currentSize--;
        return data;
    }

    T peek() override {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return T();
        }

        return this->arr[front];
    }

    T getAt(int position) {
        int index = (front + position) % this->maxSize;
        return this->arr[index];
    }

    int getCount() {
        return this->currentSize;
    }
};

const int MAX_SIZE = 5;

struct Customer {
    string name;
    string transaction;
};

void showCustomer(Customer c) {
    cout << "Name: " << c.name
         << ", Transaction: " << c.transaction << "\n";
}

void display(MyQueue<Customer>& queue) {
    if (queue.isEmpty()) {
        cout << "No customers are waiting.\n";
        return;
    }

    cout << "\nCustomers Waiting:\n";
    for (int i = 0; i < queue.getCount(); i++) {
        showCustomer(queue.getAt(i));
    }
}

int main() {
    MyQueue<Customer> queue(MAX_SIZE);
    Customer c, served;
    int choice;

    do {
        cout << "\n===== BANK CUSTOMER QUEUE =====\n";
        cout << "1. Add a customer\n";
        cout << "2. Serve a customer\n";
        cout << "3. Display waiting customers\n";
        cout << "4. Show total customers waiting\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cin.ignore();
                cout << "Enter customer name: ";
                getline(cin, c.name);
                cout << "Enter transaction type: ";
                getline(cin, c.transaction);

                if (queue.isFull()) {
                    cout << "Queue is full. Cannot add customer.\n";
                } else {
                    queue.enqueue(c);
                    cout << "Customer added successfully.\n";
                }
                break;

            case 2:
                // The first customer is served first (FIFO).
                if (queue.isEmpty()) {
                    queue.dequeue();
                } else {
                    served = queue.dequeue();
                    cout << "Served Customer: ";
                    showCustomer(served);
                }
                break;

            case 3:
                display(queue);
                break;

            case 4:
                cout << "Total customers waiting: " << queue.getCount() << "\n";
                break;

            case 0:
                cout << "Exiting bank queue system...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
