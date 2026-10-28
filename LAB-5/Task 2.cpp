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
    T* minArr;
    int capacity;
    int stack;
    int minStack;

public:
    myStack(int size) {
        capacity = size;
        arr = new T[capacity];
        minArr = new T[capacity];
        stack = -1;
        minStack = -1;
    }
    void push(T value) override {
        if (isFull()) {
            cout << "Stack Overflow! Stack is full." << endl;
            return;
        }
        arr[++stack] = value;
        if (minStack == -1 || value <= minArr[minStack]) {
            minArr[++minStack] = value;
        }

        cout << value << " pushed into stack." << endl;
    }
    T pop() override {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return T();
        }
        T value = arr[stack--];
        if (value == minArr[minStack]) {
            minStack--;
        }
        return value;
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
    T getMin() const {
        if (isEmpty()) {
            cout << "Stack is empty. No minimum element." << endl;
            return T();
        }
        return minArr[minStack];
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
        delete[] minArr;
    }
};
int main() {
    int size;
    cout << "Enter the size of stack: ";
    cin >> size;

    if (size <= 0) {
        cout << "Invalid stack size." << endl;
        return 0;
    }
    myStack<int> s(size);
    int choice, value;
    do {
        cout << "\n===== STACK MENU =====" << endl;
        cout << "1. Push element" << endl;
        cout << "2. Pop element" << endl;
        cout << "3. Show top element" << endl;
        cout << "4. Check if stack is empty" << endl;
        cout << "5. Check if stack is full" << endl;
        cout << "6. Display stack elements" << endl;
        cout << "7. Show minimum element" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter value to push: ";
            cin >> value;
            s.push(value);
            break;
        case 2:
            if (!s.isEmpty()) {
                cout << "Popped element: " << s.pop() << endl;
            }
            else {
                cout << "Stack is empty." << endl;
            }
            break;
        case 3:
            if (!s.isEmpty()) {
                cout << "Top element: " << s.top() << endl;
            }
            else {
                cout << "Stack is empty." << endl;
            }
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
        case 7:
            if (!s.isEmpty())
                cout << "Minimum element: " << s.getMin() << endl;
            else
                cout << "Stack is empty." << endl;
            break;
        case 8:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 8);
    return 0;
}
