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
            cout << "Queue is empty. No booking to cancel.\n";
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

struct Booking {
    int customerID;
    string customerName;
    int numberOfTickets;
};

void showBooking(Booking b) {
    cout << "Customer ID: " << b.customerID
         << ", Name: " << b.customerName
         << ", Tickets: " << b.numberOfTickets << "\n";
}

void display(MyQueue<Booking>& queue) {
    if (queue.isEmpty()) {
        cout << "No bookings are available.\n";
        return;
    }

    cout << "\nAll Bookings:\n";
    for (int i = 0; i < queue.getCount(); i++) {
        showBooking(queue.getAt(i));
    }
}

int main() {
    MyQueue<Booking> queue(MAX_SIZE);
    Booking b, cancelled, nextBooking;
    int choice;

    do {
        cout << "\n===== CINEMA TICKET BOOKING =====\n";
        cout << "1. Book tickets\n";
        cout << "2. Cancel the first booking\n";
        cout << "3. Display the next booking\n";
        cout << "4. Display all bookings\n";
        cout << "5. Show total number of bookings\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter customer ID: ";
                cin >> b.customerID;
                cin.ignore();
                cout << "Enter customer name: ";
                getline(cin, b.customerName);
                cout << "Enter number of tickets: ";
                cin >> b.numberOfTickets;

                if (queue.isFull()) {
                    cout << "Booking queue is full. Cannot add booking.\n";
                } else {
                    queue.enqueue(b);
                    cout << "Booking added successfully.\n";
                }
                break;

            case 2:
                // The first booking is cancelled according to FIFO order.
                if (queue.isEmpty()) {
                    queue.dequeue();
                } else {
                    cancelled = queue.dequeue();
                    cout << "Cancelled Booking: ";
                    showBooking(cancelled);
                }
                break;

            case 3:
                // peek shows the next booking without removing it.
                if (queue.isEmpty()) {
                    queue.peek();
                } else {
                    nextBooking = queue.peek();
                    cout << "Next Booking:\n";
                    showBooking(nextBooking);
                }
                break;

            case 4:
                display(queue);
                break;

            case 5:
                cout << "Total bookings: " << queue.getCount() << "\n";
                break;

            case 6:
                cout << "Exiting cinema booking system...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
