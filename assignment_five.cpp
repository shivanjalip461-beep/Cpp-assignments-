// Bank Account Management System
// Concepts: Class, Objects, this pointer, Inline function,
//           Static member function, Friend class

#include <iostream>
#include <string>
using namespace std;

class Auditor;   // forward declaration (needed for the friend declaration)

// ---------------------------------------------------------------
// Class: Account  (represents one bank account)
// ---------------------------------------------------------------
class Account {
private:
    int    accNo;               // account number
    string holder;              // account holder's name
    double balance;             // current balance
    static int totalAccounts;   // static data member shared by all objects

public:
    // Parameterized constructor.
    // Parameter names are the same as data members, so the
    // 'this' pointer is used to tell them apart.
    Account(int accNo, string holder, double balance) {
        this->accNo   = accNo;
        this->holder  = holder;
        this->balance = balance;
        totalAccounts++;        // every new object increases the count
    }

    // Inline function (defined inside the class -> implicitly inline)
    double getBalance() const { return balance; }

    // Deposit money; returns *this so calls can be chained
    Account& deposit(double amount) {
        if (amount > 0)
            this->balance += amount;
        return *this;           // 'this' points to the calling object
    }

    // Withdraw money; refuses if balance is not enough
    Account& withdraw(double amount) {
        if (amount > this->balance)
            cout << "  [Warning] Insufficient balance for withdrawal of "
                 << amount << endl;
        else
            this->balance -= amount;
        return *this;
    }

    // Uses 'this' to compare the calling object with another object
    Account& richer(Account &other) {
        if (this->balance >= other.balance)
            return *this;
        return other;
    }

    // Inline function declared here, defined outside with 'inline' keyword
    inline void display() const;

    // Static member function: works without any object and
    // can access only static data members
    static int getTotalAccounts() { return totalAccounts; }

    // Friend class: Auditor can access private members of Account
    friend class Auditor;
};

// Initialise the static data member outside the class
int Account::totalAccounts = 0;

// Definition of the inline function
inline void Account::display() const {
    cout << "  Account No : " << accNo   << endl;
    cout << "  Holder     : " << holder  << endl;
    cout << "  Balance    : Rs. " << balance << endl;
}

// ---------------------------------------------------------------
// Class: Auditor  (friend of Account)
// ---------------------------------------------------------------
class Auditor {
public:
    // Directly reads the PRIVATE members of Account (allowed: friend)
    void audit(const Account &a) {
        cout << "  Audit -> " << a.holder << " (A/c " << a.accNo << "): ";
        if (a.balance < 1000)
            cout << "LOW BALANCE ALERT" << endl;
        else
            cout << "Balance is healthy" << endl;
    }
};

// ---------------------------------------------------------------
// main
// ---------------------------------------------------------------
int main() {
    int    no1, no2;
    string name1, name2;
    double bal1, bal2, dep, wd;

    cout << "Enter account no, name, balance for Account 1: ";
    cin >> no1 >> name1 >> bal1;
    cout << "Enter account no, name, balance for Account 2: ";
    cin >> no2 >> name2 >> bal2;
    cout << "Enter deposit amount and withdrawal amount for Account 1: ";
    cin >> dep >> wd;

    Account acc1(no1, name1, bal1);   // objects created
    Account acc2(no2, name2, bal2);

    cout << "\n--- Account Details ---" << endl;
    cout << "Account 1:" << endl;  acc1.display();
    cout << "Account 2:" << endl;  acc2.display();

    cout << "\n--- Transactions on Account 1 (method chaining) ---" << endl;
    acc1.deposit(dep).withdraw(wd);   // possible because of 'return *this'
    acc1.display();
    cout << "  Current balance (inline getter): Rs. "
         << acc1.getBalance() << endl;

    cout << "\n--- Static Member Function ---" << endl;
    cout << "  Total accounts created: "
         << Account::getTotalAccounts() << endl;   // called using class name

    cout << "\n--- Richer Account (this pointer) ---" << endl;
    cout << "Account with higher balance:" << endl;
    acc1.richer(acc2).display();

    cout << "\n--- Friend Class Auditor ---" << endl;
    Auditor aud;
    aud.audit(acc1);
    aud.audit(acc2);

    return 0;
}
