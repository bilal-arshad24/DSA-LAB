#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    int studentId;
    string name;
    string priority;
    int priorityLevel;
    Student* next;

    Student(int id, string name, string priority, int level) {
        this->studentId = id;
        this->name = name;
        this->priority = priority;
        this->priorityLevel = level;
        this->next = nullptr;
    }
};

class ReservationQueue {
public:
    string bookTitle;
    Student* head;

    ReservationQueue(string title) {
        bookTitle = title;
        head = nullptr;
    }

    // A smaller number represents a higher reservation priority.
    int getPriorityLevel(string p) {
        if (p == "Research") return 1;
        if (p == "Assignment") return 2;
        if (p == "Casual") return 3;
        return 3;
    }

    void addStudent(int id, string name, string priority) {
        Student* newStudent = new Student(id, name, priority, getPriorityLevel(priority));

        if (head == nullptr) {
            head = newStudent;
            cout << "Added " << name << " (ID: " << id << ", Priority: " << priority
                 << ") to reservation list for \"" << bookTitle << "\".\n";
            return;
        }

        Student* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newStudent;
        cout << "Added " << name << " (ID: " << id << ", Priority: " << priority
             << ") to reservation list for \"" << bookTitle << "\".\n";
    }

    void removeStudent(int id) {
        if (head == nullptr) {
            cout << "Reservation list for \"" << bookTitle << "\" is empty.\n";
            return;
        }

        if (head->studentId == id) {
            Student* toRemove = head;
            head = head->next;
            cout << "Removed " << toRemove->name << " (ID: " << toRemove->studentId
                 << ") from \"" << bookTitle << "\" reservation list.\n";
            delete toRemove;
            return;
        }

        Student* temp = head;
        while (temp->next != nullptr && temp->next->studentId != id) {
            temp = temp->next;
        }

        if (temp->next == nullptr) {
            cout << "Student with ID " << id << " not found in \"" << bookTitle
                 << "\" reservation list.\n";
            return;
        }

        Student* toRemove = temp->next;
        temp->next = toRemove->next;
        cout << "Removed " << toRemove->name << " (ID: " << toRemove->studentId
             << ") from \"" << bookTitle << "\" reservation list.\n";
        delete toRemove;
    }

    void updatePriority(int id, string newPriority) {
        if (head == nullptr) {
            cout << "Reservation list for \"" << bookTitle << "\" is empty.\n";
            return;
        }

        Student* target = nullptr;
        Student* temp = head;
        while (temp != nullptr) {
            if (temp->studentId == id) {
                target = temp;
                break;
            }
            temp = temp->next;
        }

        if (target == nullptr) {
            cout << "Student with ID " << id << " not found in \"" << bookTitle
                 << "\" reservation list.\n";
            return;
        }

        string oldPriority = target->priority;
        int newLevel = getPriorityLevel(newPriority);
        target->priority = newPriority;
        target->priorityLevel = newLevel;

        if (newLevel == getPriorityLevel(oldPriority)) {
            cout << "Student " << target->name << " priority updated from "
                 << oldPriority << " to " << newPriority
                 << " (position unchanged — same priority level).\n";
            return;
        }

        if (newLevel > getPriorityLevel(oldPriority)) {
            cout << "Student " << target->name << " priority changed from "
                 << oldPriority << " to " << newPriority
                 << " (demoted — position in queue may drop).\n";
        } else {
            cout << "Student " << target->name << " priority changed from "
                 << oldPriority << " to " << newPriority
                 << " (promoted — moving up the queue).\n";
        }

        reorderByPriority(target);
    }

    void reorderByPriority(Student* target) {
        if (head == target && target->next == nullptr) return;

        if (head == target) {
            head = target->next;
        } else {
            Student* prev = head;
            while (prev->next != target) {
                prev = prev->next;
            }
            prev->next = target->next;
        }

        // Remove the student first, then place them at the correct priority position.
        target->next = nullptr;

        if (head == nullptr || head->priorityLevel > target->priorityLevel) {
            target->next = head;
            head = target;
            return;
        }

        Student* insertAfter = head;
        // Keep students with the same priority in their existing order.
        while (insertAfter->next != nullptr &&
               insertAfter->next->priorityLevel <= target->priorityLevel) {
            insertAfter = insertAfter->next;
        }

        target->next = insertAfter->next;
        insertAfter->next = target;
    }

    void display() const {
        if (head == nullptr) {
            cout << "No students waiting for \"" << bookTitle << "\".\n";
            return;
        }

        cout << "\n--- Reservation Queue for \"" << bookTitle << "\" ---\n";
        cout << "Pos | ID    | Name             | Priority\n";
        cout << "----|-------|------------------|-------------\n";

        Student* temp = head;
        int pos = 1;
        while (temp != nullptr) {
            cout << pos << "   | " << temp->studentId << "   | " << temp->name;
            for (size_t i = temp->name.length(); i < 17; i++) cout << " ";
            cout << "| " << temp->priority << "\n";
            temp = temp->next;
            pos++;
        }
        cout << "-----------------------------------------------\n";
    }

    int count() const {
        int c = 0;
        Student* temp = head;
        while (temp != nullptr) {
            c++;
            temp = temp->next;
        }
        return c;
    }

    void serveNext() {
        if (head == nullptr) {
            cout << "No one waiting for \"" << bookTitle << "\".\n";
            return;
        }

        // The first student has the highest priority, so serve the head node.
        Student* served = head;
        head = head->next;
        cout << "Book \"" << bookTitle << "\" returned. Serving "
             << served->name << " (ID: " << served->studentId
             << ", Priority: " << served->priority << ").\n";
        delete served;
    }

    ~ReservationQueue() {
        Student* current = head;
        while (current != nullptr) {
            Student* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

class Library {
private:
    ReservationQueue* books[10];
    int bookCount;

public:
    Library() {
        bookCount = 0;
    }

    void addBook(string title) {
        if (bookCount >= 10) {
            cout << "Library cannot hold more books.\n";
            return;
        }
        books[bookCount] = new ReservationQueue(title);
        bookCount++;
    }

    ReservationQueue* findBook(string title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->bookTitle == title) {
                return books[i];
            }
        }
        return nullptr;
    }

    ReservationQueue* findBookByIndex(int index) {
        if (index >= 0 && index < bookCount) {
            return books[index];
        }
        return nullptr;
    }

    void listBooks() const {
        cout << "\n--- Books in Library ---\n";
        for (int i = 0; i < bookCount; i++) {
            cout << i + 1 << ". \"" << books[i]->bookTitle << "\" ("
                 << books[i]->count() << " waiting)\n";
        }
    }

    int getBookCount() const {
        return bookCount;
    }

    ~Library() {
        for (int i = 0; i < bookCount; i++) {
            delete books[i];
        }
    }
};

int main() {
    Library library;
    library.addBook("Introduction to Algorithms");
    library.addBook("Clean Code");

    cout << "========== SAMPLE DEMONSTRATION ==========\n";

    ReservationQueue* algo = library.findBook("Introduction to Algorithms");
    ReservationQueue* clean = library.findBook("Clean Code");

    cout << "\n>>> Adding students to \"Introduction to Algorithms\"\n";
    algo->addStudent(201, "Ali Hassan", "Casual");
    algo->addStudent(202, "Fatima Noor", "Assignment");
    algo->addStudent(203, "Usman Tariq", "Research");
    algo->addStudent(204, "Zara Sheikh", "Casual");
    algo->addStudent(205, "Bilal Raza", "Assignment");

    cout << "\n>>> Adding students to \"Clean Code\"\n";
    clean->addStudent(301, "Hina Iqbal", "Casual");
    clean->addStudent(302, "Ahmed Khan", "Research");
    clean->addStudent(303, "Maryam Yousaf", "Assignment");

    cout << "\n>>> Displaying both books' queues\n";
    algo->display();
    clean->display();

    cout << "\n>>> Counting students per book\n";
    cout << "\"" << algo->bookTitle << "\": " << algo->count() << " students\n";
    cout << "\"" << clean->bookTitle << "\": " << clean->count() << " students\n";

    cout << "\n>>> Zara Sheikh (ID 204) upgrades to Research priority\n";
    algo->updatePriority(204, "Research");
    algo->display();

    cout << "\n>>> Usman Tariq (ID 203) downgrades to Casual priority\n";
    algo->updatePriority(203, "Casual");
    algo->display();

    cout << "\n>>> Fatima Noor (ID 202) cancels her reservation\n";
    algo->removeStudent(202);
    algo->display();

    cout << "\n>>> Book \"Introduction to Algorithms\" is returned — serve next\n";
    algo->serveNext();
    algo->display();

    cout << "\n>>> Book \"Clean Code\" is returned — serve next\n";
    clean->serveNext();
    clean->display();

    cout << "\n>>> Attempting to remove non-existent student ID 999\n";
    algo->removeStudent(999);

    cout << "\n========== END OF DEMONSTRATION ==========\n";
    cout << "Switching to interactive mode...\n";

    int choice;
    do {
        cout << "\n===== UNIVERSITY LIBRARY RESERVATION SYSTEM =====\n";
        cout << "1. List all books\n";
        cout << "2. Add student to a book's reservation list\n";
        cout << "3. Remove student (cancel reservation)\n";
        cout << "4. Update student priority\n";
        cout << "5. Display reservation list for a book\n";
        cout << "6. Count students in a book's list\n";
        cout << "7. Serve next student (book returned)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 7) {
            library.listBooks();
        }

        int bookNum, id;
        string name, priority;

        switch (choice) {
            case 1:
                break;

            case 2:
                cout << "Select book number: ";
                cin >> bookNum;
                if (library.findBookByIndex(bookNum - 1) == nullptr) {
                    cout << "Invalid book.\n";
                    break;
                }
                cout << "Student ID: ";
                cin >> id;
                cin.ignore();
                cout << "Student name: ";
                getline(cin, name);
                cout << "Priority (Research / Assignment / Casual): ";
                getline(cin, priority);
                library.findBookByIndex(bookNum - 1)->addStudent(id, name, priority);
                break;

            case 3:
                cout << "Select book number: ";
                cin >> bookNum;
                if (library.findBookByIndex(bookNum - 1) == nullptr) {
                    cout << "Invalid book.\n";
                    break;
                }
                cout << "Student ID to remove: ";
                cin >> id;
                library.findBookByIndex(bookNum - 1)->removeStudent(id);
                break;

            case 4:
                cout << "Select book number: ";
                cin >> bookNum;
                if (library.findBookByIndex(bookNum - 1) == nullptr) {
                    cout << "Invalid book.\n";
                    break;
                }
                cout << "Student ID: ";
                cin >> id;
                cin.ignore();
                cout << "New priority (Research / Assignment / Casual): ";
                getline(cin, priority);
                library.findBookByIndex(bookNum - 1)->updatePriority(id, priority);
                break;

            case 5:
                cout << "Select book number: ";
                cin >> bookNum;
                if (library.findBookByIndex(bookNum - 1) == nullptr) {
                    cout << "Invalid book.\n";
                    break;
                }
                library.findBookByIndex(bookNum - 1)->display();
                break;

            case 6:
                cout << "Select book number: ";
                cin >> bookNum;
                if (library.findBookByIndex(bookNum - 1) == nullptr) {
                    cout << "Invalid book.\n";
                    break;
                }
                cout << "Students waiting: "
                     << library.findBookByIndex(bookNum - 1)->count() << "\n";
                break;

            case 7:
                cout << "Select book number: ";
                cin >> bookNum;
                if (library.findBookByIndex(bookNum - 1) == nullptr) {
                    cout << "Invalid book.\n";
                    break;
                }
                library.findBookByIndex(bookNum - 1)->serveNext();
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