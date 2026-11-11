#include <iostream>
using namespace std;

// Each node stores data and the address of the next node.
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    void CreateNode(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        // Move to the last node before adding the new node.
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    void Display() const {
        if (head == nullptr) {
            cout << "List is empty."<<endl;
            return;
        }

        Node* temp = head;
        cout << "Linked List: ";
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << " -> NULL\n";
    }

    ~SinglyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            // Save the next address before deleting the current node.
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    SinglyLinkedList list;

    cout << "--- Initial state ---";
    list.Display();

    cout << "--- Adding nodes ---";
    list.CreateNode(10);
    list.CreateNode(20);
    list.CreateNode(30);
    list.CreateNode(40);
    list.CreateNode(50);

    cout << "--- Final list ---";
    list.Display();

    return 0;
}