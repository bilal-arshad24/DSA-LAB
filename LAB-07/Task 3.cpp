#include <iostream>
using namespace std;

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

    void insertAtPosition(int value, int position) {
        if (position < 1) {
            cout << "Invalid position! Position must be >= 1.\n";
            return;
        }

        Node* newNode = new Node(value);

        if (position == 1) {
            newNode->next = head;
            head = newNode;
            cout << "Inserted " << value << " at position 1.\n";
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Position " << position << " is out of range. List has fewer nodes.\n";
            delete newNode;
            return;
        }

        // Connect the new node with the next node first.
        newNode->next = temp->next;
        temp->next = newNode;
        cout << "Inserted " << value << " at position " << position << ".\n";
    }

    void deleteAtPosition(int position) {
        if (head == nullptr) {
            cout << "List is empty. Cannot delete.\n";
            return;
        }

        if (position < 1) {
            cout << "Invalid position! Position must be >= 1.\n";
            return;
        }

        if (position == 1) {
            Node* toDelete = head;
            head = head->next;
            cout << "Deleted " << toDelete->data << " from position 1.\n";
            delete toDelete;
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }

        if (temp == nullptr || temp->next == nullptr) {
            cout << "Position " << position << " is out of range.\n";
            return;
        }

        // Bypass the selected node, then delete it.
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        cout << "Deleted " << toDelete->data << " from position " << position << ".\n";
        delete toDelete;
    }

    void search(int value) const {
        if (head == nullptr) {
            cout << "List is empty. Value " << value << " not found.\n";
            return;
        }

        Node* temp = head;
        int position = 1;
        // Check each node and keep track of its position.
        while (temp != nullptr) {
            if (temp->data == value) {
                cout << "Value " << value << " found at position " << position << ".\n";
                return;
            }
            temp = temp->next;
            position++;
        }

        cout << "Value " << value << " NOT found in the list.\n";
    }

    int countNodes() const {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        cout << "List: ";
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
            // Save the next node before deleting the current one.
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    SinglyLinkedList list;
    int choice, value, position;

    do {
        cout << "\n===== SINGLY LINKED LIST MENU =====\n";
        cout << "1. Insert node at a specific position\n";
        cout << "2. Delete node at a specific position\n";
        cout << "3. Search for an element\n";
        cout << "4. Count total number of nodes\n";
        cout << "5. Display list\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                cout << "Enter position: ";
                cin >> position;
                list.insertAtPosition(value, position);
                break;

            case 2:
                cout << "Enter position to delete: ";
                cin >> position;
                list.deleteAtPosition(position);
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                list.search(value);
                break;

            case 4:
                cout << "Total nodes: " << list.countNodes() << "\n";
                break;

            case 5:
                list.display();
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