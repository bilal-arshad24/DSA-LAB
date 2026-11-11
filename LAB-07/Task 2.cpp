#include <iostream>
using namespace std;

// This abstract class defines the common operations of a list.
template <typename T>
class AbstractList {
public:
    virtual void insertAtBeginning(T value) = 0;
    virtual void insertAtEnd(T value) = 0;
    virtual bool deleteByValue(T value) = 0;
    virtual void display() const = 0;
    virtual bool isEmpty() const = 0;
    virtual ~AbstractList() {}
};

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T value) {
        data = value;
        next = nullptr;
    }
};

template <typename T>
class SinglyLinkedList : public AbstractList<T> {
private:
    Node<T>* head;

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    void insertAtBeginning(T value) override {
        Node<T>* newNode = new Node<T>(value);
        // Make the new node point to the old first node.
        newNode->next = head;
        head = newNode;
        cout << "Inserted " << value << " at beginning.\n";
    }

    void insertAtEnd(T value) override {
        Node<T>* newNode = new Node<T>(value);

        if (head == nullptr) {
            head = newNode;
            cout << "Inserted " << value << " at end.\n";
            return;
        }

        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        cout << "Inserted " << value << " at end.\n";
    }

    bool deleteByValue(T value) override {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete " << value << ".\n";
            return false;
        }

        if (head->data == value) {
            Node<T>* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Deleted " << value << " from list.\n";
            return true;
        }

        Node<T>* temp = head;
        while (temp->next != nullptr && temp->next->data != value) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Value " << value << " not found in list.\n";
            return false;
        }

        // Skip the node that needs to be removed.
        Node<T>* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        cout << "Deleted " << value << " from list.\n";
        return true;
    }

    void display() const override {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node<T>* temp = head;
        cout << "List: ";
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << " -> NULL\n";
    }

    bool isEmpty() const override {
        return head == nullptr;
    }

    ~SinglyLinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            // Delete every node to release the allocated memory.
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    SinglyLinkedList<int> list;
    int choice, value;

    do {
        cout << "\n===== SINGLY LINKED LIST MENU =====\n";
        cout << "1. Insert at beginning\n";
        cout << "2. Insert at end\n";
        cout << "3. Delete by value\n";
        cout << "4. Display list\n";
        cout << "5. Check if empty\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                list.insertAtBeginning(value);
                break;

            case 2:
                cout << "Enter value: ";
                cin >> value;
                list.insertAtEnd(value);
                break;

            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteByValue(value);
                break;

            case 4:
                list.display();
                break;

            case 5:
                cout << (list.isEmpty() ? "List is empty.\n" : "List is NOT empty.\n");
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}