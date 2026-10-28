
#include <iostream>
using namespace std;

template <typename T>
class AbstractStack {
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractStack() {}
};

template <typename T>
class myStack : public AbstractStack<T> {
private:
    T* arr;
    int capacity;
    int stack;

public:
    myStack(int size) {
        capacity = size;
        arr = new T[capacity];
        stack = -1;
    }

    void push(T value) override {
        if (isFull()) {
            cout << "Stack Overflow! Stack is full." << endl;
            return;
        }

        arr[++stack] = value;
        cout << value << " stored in stack." << endl;
    }

    T pop() override {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return T();
        }

        return arr[stack--];
    }

    T top() const override {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return T();
        }

        return arr[stack];
    }

    bool isEmpty() const override {
        return stack == -1;
    }

    bool isFull() const override {
        return stack == capacity - 1;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Stack (Top to Bottom):" << endl;

        for (int i = stack; i >= 0; i--) {
            cout << arr[i] << endl;
        }
    }

    ~myStack() override {
        delete[] arr;
    }
};

int main() {
    int size;

    cout << "Enter the size of stack: " << endl;
    cin >> size;

    if (size <= 0) {
        cout << "Invalid stack size." << endl;
        return 0;
    }

    myStack<int> s(size);

    int choice, value;

    do {
        cout << "\n===== STACK MENU =====\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Top\n";
        cout << "4. Check Empty\n";
        cout << "5. Check Full\n";
        cout << "6. Display Stack\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> value;
            s.push(value);
            break;

        case 2:
            if (!s.isEmpty())
                cout << "Popped element: " << s.pop() << endl;
            else
                cout << "Stack is empty." << endl;
            break;

        case 3:
            if (!s.isEmpty())
                cout << "Top element: " << s.top() << endl;
            else
                cout << "Stack is empty." << endl;
            break;

        case 4:
            if (s.isEmpty())
                cout << "Stack is empty." << endl;
            else
                cout << "Stack is not empty." << endl;
            break;

        case 5:
            if (s.isFull())
                cout << "Stack is full." << endl;
            else
                cout << "Stack is not full." << endl;
            break;

        case 6:
            s.display();
            break;

        case 0:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
