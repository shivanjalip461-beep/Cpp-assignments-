// College Management System
// Concepts: Single, Multilevel, Hierarchical, Multiple and Hybrid Inheritance
#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// Base class: Person (used for Single, Multilevel, Hierarchical)
// ---------------------------------------------------------------
class Person {
protected:                      // visible to derived classes only
    string name;
    int id;
public:
    Person(string n, int i) : name(n), id(i) {
        cout << "   [Person constructor]    " << name << endl;
    }
    void displayPerson() const {
        cout << "   Name : " << name << "  |  ID : " << id << endl;
    }
    ~Person() { cout << "   [Person destructor]     " << name << endl; }
};

// ---------------------------------------------------------------
// 1. SINGLE INHERITANCE : Person -> Student
// ---------------------------------------------------------------
class Student : public Person {
protected:
    string department;
    float cgpa;
public:
    Student(string n, int i, string d, float c)
        : Person(n, i), department(d), cgpa(c) {
        cout << "   [Student constructor]   " << name << endl;
    }
    void displayStudent() const {
        displayPerson();
        cout << "   Department : " << department << "  |  CGPA : " << cgpa << endl;
    }
    ~Student() { cout << "   [Student destructor]    " << name << endl; }
};

// ---------------------------------------------------------------
// 2. MULTILEVEL INHERITANCE : Person -> Employee -> Professor
// ---------------------------------------------------------------
class Employee : public Person {
protected:
    double salary;
public:
    Employee(string n, int i, double s) : Person(n, i), salary(s) {
        cout << "   [Employee constructor]  " << name << endl;
    }
    void displayEmployee() const {
        displayPerson();
        cout << "   Salary : Rs. " << salary << endl;
    }
    ~Employee() { cout << "   [Employee destructor]   " << name << endl; }
};

class Professor : public Employee {
private:
    string subject;
public:
    Professor(string n, int i, double s, string sub)
        : Employee(n, i, s), subject(sub) {
        cout << "   [Professor constructor] " << name << endl;
    }
    void displayProfessor() const {
        displayEmployee();
        cout << "   Subject taught : " << subject << endl;
    }
    ~Professor() { cout << "   [Professor destructor]  " << name << endl; }
};

// ---------------------------------------------------------------
// 3. HIERARCHICAL INHERITANCE : Employee -> Professor, Employee -> Clerk
// ---------------------------------------------------------------
class Clerk : public Employee {
private:
    string section;
public:
    Clerk(string n, int i, double s, string sec)
        : Employee(n, i, s), section(sec) {
        cout << "   [Clerk constructor]     " << name << endl;
    }
    void displayClerk() const {
        displayEmployee();
        cout << "   Section : " << section << endl;
    }
    ~Clerk() { cout << "   [Clerk destructor]      " << name << endl; }
};

// ---------------------------------------------------------------
// 4. MULTIPLE INHERITANCE : Student + Sports -> SportsStudent
// ---------------------------------------------------------------
class Sports {
protected:
    string sport;
public:
    Sports(string s) : sport(s) {
        cout << "   [Sports constructor]    " << sport << endl;
    }
    void displaySports() const {
        cout << "   Represents college in : " << sport << endl;
    }
    ~Sports() { cout << "   [Sports destructor]     " << sport << endl; }
};

class SportsStudent : public Student, public Sports {
public:
    SportsStudent(string n, int i, string d, float c, string s)
        : Student(n, i, d, c), Sports(s) {
        cout << "   [SportsStudent constructor] " << name << endl;
    }
    void displayAll() const {
        displayStudent();       // from Student (and Person)
        displaySports();        // from Sports
    }
    ~SportsStudent() { cout << "   [SportsStudent destructor]  " << name << endl; }
};

// ---------------------------------------------------------------
// 5. HYBRID INHERITANCE (Hierarchical + Multiple = diamond shape)
//
//   LibraryMember is the base of both StudentMember and StaffMember;
//   ResearchScholar then inherits from both of them.
//   'virtual' inheritance keeps only ONE copy of LibraryMember.
// ---------------------------------------------------------------
class LibraryMember {
protected:
    int memberId;
    string memberName;
public:
    LibraryMember(int id, string n) : memberId(id), memberName(n) {
        cout << "   [LibraryMember constructor]   " << memberName << endl;
    }
    void displayMember() const {
        cout << "   Member ID : " << memberId << "  |  Name : " << memberName << endl;
    }
    ~LibraryMember() { cout << "   [LibraryMember destructor]    " << memberName << endl; }
};

class StudentMember : virtual public LibraryMember {
protected:
    string course;
public:
    StudentMember(int id, string n, string c) : LibraryMember(id, n), course(c) {
        cout << "   [StudentMember constructor]   " << memberName << endl;
    }
    ~StudentMember() { cout << "   [StudentMember destructor]    " << memberName << endl; }
};

class StaffMember : virtual public LibraryMember {
protected:
    string designation;
public:
    StaffMember(int id, string n, string d) : LibraryMember(id, n), designation(d) {
        cout << "   [StaffMember constructor]     " << memberName << endl;
    }
    ~StaffMember() { cout << "   [StaffMember destructor]      " << memberName << endl; }
};

// A research scholar is a student AND works as a research assistant
class ResearchScholar : public StudentMember, public StaffMember {
public:
    // the most derived class initialises the virtual base class directly
    ResearchScholar(int id, string n, string c, string d)
        : LibraryMember(id, n), StudentMember(id, n, c), StaffMember(id, n, d) {
        cout << "   [ResearchScholar constructor] " << memberName << endl;
    }
    void displayScholar() const {
        displayMember();        // only ONE copy of LibraryMember -> no ambiguity
        cout << "   Course : " << course << "  |  Designation : " << designation << endl;
    }
    ~ResearchScholar() { cout << "   [ResearchScholar destructor]  " << memberName << endl; }
};

// ---------------------------------------------------------------
// main : menu driven program
// ---------------------------------------------------------------
int main() {
    int choice;
    do {
        cout << "\n===== COLLEGE MANAGEMENT SYSTEM (INHERITANCE) =====" << endl;
        cout << "1. Single       (Person -> Student)" << endl;
        cout << "2. Multilevel   (Person -> Employee -> Professor)" << endl;
        cout << "3. Hierarchical (Employee -> Professor, Clerk)" << endl;
        cout << "4. Multiple     (Student + Sports -> SportsStudent)" << endl;
        cout << "5. Hybrid       (LibraryMember -> Student/Staff -> ResearchScholar)" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string n, d; int i; float c;
            cout << "Enter name, id, department, cgpa: ";
            cin >> n >> i >> d >> c;
            cout << "\n-- Single Inheritance --" << endl;
            Student s(n, i, d, c);
            s.displayStudent();
            break;
        }
        case 2: {
            string n, sub; int i; double sal;
            cout << "Enter professor name, id, salary, subject: ";
            cin >> n >> i >> sal >> sub;
            cout << "\n-- Multilevel Inheritance --" << endl;
            Professor p(n, i, sal, sub);
            p.displayProfessor();
            break;
        }
        case 3: {
            string pn, sub, cn, sec; int pi, ci; double ps, cs;
            cout << "Enter professor name, id, salary, subject: ";
            cin >> pn >> pi >> ps >> sub;
            cout << "Enter clerk name, id, salary, section: ";
            cin >> cn >> ci >> cs >> sec;
            cout << "\n-- Hierarchical Inheritance --" << endl;
            Professor p(pn, pi, ps, sub);
            Clerk c(cn, ci, cs, sec);
            p.displayProfessor();
            c.displayClerk();
            break;
        }
        case 4: {
            string n, d, sp; int i; float c;
            cout << "Enter name, id, department, cgpa, sport: ";
            cin >> n >> i >> d >> c >> sp;
            cout << "\n-- Multiple Inheritance --" << endl;
            SportsStudent ss(n, i, d, c, sp);
            ss.displayAll();
            break;
        }
        case 5: {
            string n, course, desig; int id;
            cout << "Enter name, member id, course, designation: ";
            cin >> n >> id >> course >> desig;
            cout << "\n-- Hybrid Inheritance --" << endl;
            ResearchScholar rs(id, n, course, desig);
            rs.displayScholar();
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
