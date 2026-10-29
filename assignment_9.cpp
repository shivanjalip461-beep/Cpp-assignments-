// Student Record Management System
// Concepts: std::move (<utility>), Move Constructor, Move Assignment, Rule of Five
// Note: compile with C++11 or later (Dev-C++: Tools > Compiler Options > Settings >
//       Code Generation > Language standard (-std) > ISO C++11 / C++14)
#include <iostream>
#include <string>
#include <vector>
#include <utility>   // std::move
using namespace std;

// ---------------------------------------------------------------
// Class: StudentRecord
// Owns a dynamically allocated array of marks, so it needs
// proper copy and move operations (Rule of Five).
// ---------------------------------------------------------------
class StudentRecord {
private:
    string name;
    int*   marks;      // dynamic array (the resource that is copied or moved)
    int    count;      // number of subjects

public:
    // Parameterized constructor (all marks filled with the value m)
    StudentRecord(string n, int c, int m = 0) : name(n), marks(new int[c]), count(c) {
        for (int i = 0; i < count; i++)
            marks[i] = m;
        cout << " [Constructor] " << name << endl;
    }

    // Copy constructor : allocates new memory and copies every mark (deep copy)
    StudentRecord(const StudentRecord& other)
        : name(other.name + "_copy"), marks(new int[other.count]), count(other.count) {
        for (int i = 0; i < count; i++)
            marks[i] = other.marks[i];
        cout << " [Copy Constructor] " << name << endl;
    }

    // Move constructor : steals the pointer, no new memory is allocated
    StudentRecord(StudentRecord&& other) noexcept
        : name(std::move(other.name)), marks(other.marks), count(other.count) {
        other.marks = nullptr;   // source no longer owns the memory
        other.count = 0;
        cout << " [Move Constructor] " << name << endl;
    }

    // Copy assignment operator : deep copy
    StudentRecord& operator=(const StudentRecord& other) {
        if (this != &other) {
            delete[] marks;
            name  = other.name + "_copy";
            count = other.count;
            marks = new int[count];
            for (int i = 0; i < count; i++)
                marks[i] = other.marks[i];
        }
        cout << " [Copy Assignment] " << name << endl;
        return *this;
    }

    // Move assignment operator : frees own memory, then steals from the source
    StudentRecord& operator=(StudentRecord&& other) noexcept {
        if (this != &other) {
            delete[] marks;              // release the old resource
            name  = std::move(other.name);
            marks = other.marks;         // steal pointer
            count = other.count;
            other.marks = nullptr;       // leave the source empty
            other.count = 0;
        }
        cout << " [Move Assignment] " << name << endl;
        return *this;
    }

    void inputMarks() {
        cout << "Enter " << count << " marks: ";
        for (int i = 0; i < count; i++)
            cin >> marks[i];
    }

    void display() const {
        if (marks == nullptr) {
            cout << " Record is empty (resources moved)" << endl;
            return;
        }
        cout << " Name : " << name << " | Subjects : " << count << endl;
        cout << " Marks : ";
        for (int i = 0; i < count; i++)
            cout << marks[i] << " ";
        cout << endl;
    }

    // Destructor
    ~StudentRecord() {
        if (marks == nullptr)
            cout << " [Destructor] (moved-from object, nothing to free)" << endl;
        else
            cout << " [Destructor] " << name << endl;
        delete[] marks;      // deleting nullptr is safe
    }
};

// ---------------------------------------------------------------
// Generic swap that uses std::move (no copying of the contents)
// ---------------------------------------------------------------
template <typename T>
void mySwap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// ---------------------------------------------------------------
// main : menu driven program
// ---------------------------------------------------------------
int main() {
    int choice;
    do {
        cout << "\n===== STUDENT RECORD SYSTEM (std::move) =====" << endl;
        cout << "1. Copy Constructor vs Move Constructor" << endl;
        cout << "2. Move Assignment Operator" << endl;
        cout << "3. std::move with string and vector" << endl;
        cout << "4. Generic swap using std::move" << endl;
        cout << "5. Moving objects into a vector" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string n; int c;
                cout << "Enter name and number of subjects: ";
                cin >> n >> c;
                cout << "\n-- Copy vs Move Constructor --" << endl;
                StudentRecord a(n, c);
                a.inputMarks();
                StudentRecord b = a;                 // a is an lvalue -> copy
                b.display();
                StudentRecord m = std::move(a);      // a cast to rvalue -> move
                m.display();
                cout << " Original after move :" << endl;
                a.display();
                break;
            }
            case 2: {
                string n; int c;
                cout << "Enter name and number of subjects: ";
                cin >> n >> c;
                cout << "\n-- Move Assignment --" << endl;
                StudentRecord a(n, c);
                a.inputMarks();
                StudentRecord b("Temp", 2);
                b = std::move(a);                    // move assignment
                cout << " Target after move assignment :" << endl;
                b.display();
                cout << " Source after move assignment :" << endl;
                a.display();
                break;
            }
            case 3: {
                string s1;
                cout << "Enter a word: ";
                cin >> s1;
                cout << "\n-- std::move with string and vector --" << endl;
                cout << " Before move : s1 = " << s1 << endl;
                string s2 = std::move(s1);
                cout << " After move  : s2 = " << s2 << " | s1 length = " << s1.size() << endl;

                vector<int> v1 = {10, 20, 30, 40, 50};
                cout << " Before move : v1 size = " << v1.size() << endl;
                vector<int> v2 = std::move(v1);
                cout << " After move  : v2 size = " << v2.size()
                     << " | v1 size = " << v1.size() << endl;
                break;
            }
            case 4: {
                string s1, s2;
                int x = 10, y = 20;
                cout << "Enter two words: ";
                cin >> s1 >> s2;
                cout << "\n-- Generic swap using std::move --" << endl;
                cout << " Before swap : s1 = " << s1 << " | s2 = " << s2 << endl;
                mySwap(s1, s2);
                cout << " After swap  : s1 = " << s1 << " | s2 = " << s2 << endl;
                cout << " Before swap : x = " << x << " | y = " << y << endl;
                mySwap(x, y);
                cout << " After swap  : x = " << x << " | y = " << y << endl;
                break;
            }
            case 5: {
                string n1, n2;
                cout << "Enter two student names: ";
                cin >> n1 >> n2;
                cout << "\n-- Moving objects into a vector --" << endl;
                StudentRecord r1(n1, 3, 75);
                StudentRecord r2(n2, 3, 88);
                vector<StudentRecord> list;
                list.reserve(2);                     // avoids extra reallocation moves
                list.push_back(std::move(r1));       // moved, not copied
                list.push_back(std::move(r2));
                cout << " Records stored in vector :" << endl;
                for (size_t i = 0; i < list.size(); i++)
                    list[i].display();
                cout << " r1 after move :" << endl;
                r1.display();
                cout << " r2 after move :" << endl;
                r2.display();
                break;
            }
            case 0:
                cout << "Program ended." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
