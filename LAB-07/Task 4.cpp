#include <iostream>
#include <string>
using namespace std;

class Patient {
public:
    int id;
    string name;
    string ailment;
    Patient* next;

    Patient(int id, string name, string ailment) {
        this->id = id;
        this->name = name;
        this->ailment = ailment;
        this->next = nullptr;
    }
};

class PatientQueue {
private:
    Patient* head;

public:
    PatientQueue() {
        head = nullptr;
    }

    void addPatient(int id, string name, string ailment) {
        Patient* newPatient = new Patient(id, name, ailment);

        if (head == nullptr) {
            head = newPatient;
            cout << "Patient " << name << " (ID: " << id << ") added to the queue.\n";
            return;
        }

        // Add the new patient at the end to keep arrival order.
        Patient* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPatient;
        cout << "Patient " << name << " (ID: " << id << ") added to the queue.\n";
    }

    void removePatient(int id) {
        if (head == nullptr) {
            cout << "Queue is empty. No patient to remove.\n";
            return;
        }

        if (head->id == id) {
            Patient* toRemove = head;
            head = head->next;
            cout << "Patient " << toRemove->name << " (ID: " << toRemove->id
                 << ") removed from the queue (appointment cancelled).\n";
            delete toRemove;
            return;
        }

        Patient* temp = head;
        while (temp->next != nullptr && temp->next->id != id) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Patient with ID " << id << " not found in the queue.\n";
            return;
        }

        // Skip the patient being removed, then free that node.
        Patient* toRemove = temp->next;
        temp->next = toRemove->next;
        cout << "Patient " << toRemove->name << " (ID: " << toRemove->id
             << ") removed from the queue (appointment cancelled).\n";
        delete toRemove;
    }

    void displayPatients() const {
        if (head == nullptr) {
            cout << "Queue is empty. No patients waiting.\n";
            return;
        }

        cout << "\n--- Current Patient Queue ---\n";
        cout << "Pos | ID    | Name            | Ailment\n";
        cout << "----|-------|-----------------|-----------------\n";

        Patient* temp = head;
        int position = 1;
        while (temp != nullptr) {
            cout << position << "   | " 
                 << temp->id << "    | "
                 << temp->name;
            for (size_t i = temp->name.length(); i < 16; i++) cout << " ";
            cout << "| " << temp->ailment << "\n";
            temp = temp->next;
            position++;
        }
        cout << "-----------------------------------------------\n";
    }

    int countPatients() const {
        int count = 0;
        Patient* temp = head;
        // Visit each node once to get the total number of patients.
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    ~PatientQueue() {
        Patient* current = head;
        while (current != nullptr) {
            Patient* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

int main() {
    PatientQueue queue;
    int choice, id;
    string name, ailment;

    do {
        cout << "\n===== HOSPITAL QUEUE MANAGEMENT =====\n";
        cout << "1. Add new patient to queue\n";
        cout << "2. Remove patient (cancel appointment)\n";
        cout << "3. Display current patient list\n";
        cout << "4. Count patients in queue\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter patient ID: ";
                cin >> id;
                // Remove the leftover newline before using getline.
                cin.ignore();
                cout << "Enter patient name: ";
                getline(cin, name);
                cout << "Enter ailment/reason: ";
                getline(cin, ailment);
                queue.addPatient(id, name, ailment);
                break;

            case 2:
                cout << "Enter patient ID to remove: ";
                cin >> id;
                queue.removePatient(id);
                break;

            case 3:
                queue.displayPatients();
                break;

            case 4:
                cout << "Total patients currently in queue: "
                     << queue.countPatients() << "\n";
                break;

            case 0:
                cout << "Exiting hospital queue system...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}