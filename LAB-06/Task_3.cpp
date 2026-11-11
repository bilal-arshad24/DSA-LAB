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
            cout << "Queue is empty. No print job to process.\n";
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

struct PrintJob {
    int jobID;
    string userName;
    int pages;
};

void showPrintJob(PrintJob p) {
    cout << "Job ID: " << p.jobID
         << ", User: " << p.userName
         << ", Pages: " << p.pages << "\n";
}

void display(MyQueue<PrintJob>& queue) {
    if (queue.isEmpty()) {
        cout << "No pending print jobs.\n";
        return;
    }

    cout << "\nPending Print Jobs:\n";
    for (int i = 0; i < queue.getCount(); i++) {
        showPrintJob(queue.getAt(i));
    }
}

int main() {
    MyQueue<PrintJob> queue(MAX_SIZE);
    PrintJob p, completed, nextJob;
    int choice;

    do {
        cout << "\n===== PRINTER JOB QUEUE =====\n";
        cout << "1. Submit a new print job\n";
        cout << "2. Process the next print job\n";
        cout << "3. Display the next print job\n";
        cout << "4. Display all pending print jobs\n";
        cout << "5. Show total pending print jobs\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter print job ID: ";
                cin >> p.jobID;
                cin.ignore();
                cout << "Enter user name: ";
                getline(cin, p.userName);
                cout << "Enter number of pages: ";
                cin >> p.pages;

                if (queue.isFull()) {
                    cout << "Printer queue is full. Cannot add print job.\n";
                } else {
                    queue.enqueue(p);
                    cout << "Print job submitted successfully.\n";
                }
                break;

            case 2:
                // The first submitted print job is processed first.
                if (queue.isEmpty()) {
                    queue.dequeue();
                } else {
                    completed = queue.dequeue();
                    cout << "Completed Print Job: ";
                    showPrintJob(completed);
                }
                break;

            case 3:
                // peek shows the next job without removing it.
                if (queue.isEmpty()) {
                    queue.peek();
                } else {
                    nextJob = queue.peek();
                    cout << "Next Print Job:\n";
                    showPrintJob(nextJob);
                }
                break;

            case 4:
                display(queue);
                break;

            case 5:
                cout << "Total pending print jobs: " << queue.getCount() << "\n";
                break;

            case 6:
                cout << "Exiting printer queue system...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
