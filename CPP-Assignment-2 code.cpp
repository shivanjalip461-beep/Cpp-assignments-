#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    int id;
    string name;
    int salary;

public:
    // 1. Default Constructor
    Employee() {
        id = 0;
        name = "None";
        salary = 0;
    }

    // 2. Parameterized Constructor
    Employee(int emp_id, string emp_name, int emp_salary) {
        id = emp_id;
        name = emp_name;
        salary = emp_salary;
    }

    // 3. Copy Constructor
    Employee(const Employee &obj) {
        id = obj.id;
        name = obj.name;
        salary = obj.salary;
    }

    // Member Function 1: Add bonus
    void addBonus(int bonusAmount) {
        salary = salary + bonusAmount;
    }

    // Member Function 2: Display details
    void display() {
        cout << "ID: " << id << " | Name: " << name << " | Salary: " << salary << endl;
    }
};

int main() {
    // 1. Using Default Constructor
    cout << "--- Default Constructor ---" << endl;
    Employee e1;
    e1.display();

    // 2. Using Parameterized Constructor
    cout << "\n--- Parameterized Constructor ---" << endl;
    Employee e2(101, "Rohan", 50000);
    e2.addBonus(5000); // Adding a flat bonus
    e2.display();

    // 3. Using Copy Constructor
    cout << "\n--- Copy Constructor (Copy of Rohan) ---" << endl;
    Employee e3(e2); 
    e3.display();

    return 0;
}