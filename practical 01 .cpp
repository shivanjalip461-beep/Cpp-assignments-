#include <iostream>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;
    int marks;

public:
    // Constructor
    Student(int r, string n, int m)
    {
        rollNo = r;
        name = n;
        marks = m;
        cout << "Constructor called." << endl;
    }

    // User-defined function
    void display()
    {
        cout << "\n--- Student Details ---" << endl;
        cout << "Roll No: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Marks: " << marks << endl;
    }

    // User-defined function
    void checkResult()
    {
        if (marks >= 40)
            cout << "Result: PASS" << endl;
        else
            cout << "Result: FAIL" << endl;
    }

    // Destructor
    ~Student()
    {
        cout << "\nDestructor called." << endl;
    }
};

int main()
{
    // Creating an object
    Student s1(101, "Shivanjali", 85);

    // Calling user-defined functions
    s1.display();
    s1.checkResult();

    return 0;
}