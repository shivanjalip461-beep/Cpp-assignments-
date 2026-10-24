// Exception Handling: Bank Account Safety System
// Concepts: try, throw, catch, multiple catch blocks, custom exception classes,
//           standard exceptions, rethrowing, catch-all handler, stack unwinding
#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
using namespace std;

// ---------------------------------------------------------------
// Custom exception 1: amount is zero, negative or opening balance < 0
// ---------------------------------------------------------------
class InvalidAmountException : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid amount: value must be greater than zero (opening balance cannot be negative)";
    }
};

// ---------------------------------------------------------------
// Custom exception 2: withdrawal is more than the balance
// ---------------------------------------------------------------
class InsufficientFundsException : public exception {
    double balance, requested;
public:
    InsufficientFundsException(double bal, double req) : balance(bal), requested(req) {}
    const char* what() const noexcept override {
        return "Insufficient funds for this withdrawal";
    }
    double shortfall() const { return requested - balance; }
};

// ---------------------------------------------------------------
// Class: Session (shows stack unwinding - destructor runs on throw)
// ---------------------------------------------------------------
class Session {
public:
    Session()  { cout << "  [Session] Transaction session opened" << endl; }
    ~Session() { cout << "  [Session] Transaction session closed (cleanup done)" << endl; }
};

// ---------------------------------------------------------------
// Class: Account
// ---------------------------------------------------------------
class Account {
    int accNo;
    double balance;
    double history[5];   // last 5 transactions (+ deposit, - withdrawal)
    int count;
public:
    Account(int no, double bal) : accNo(no), balance(bal), count(0) {
        if (bal < 0)
            throw InvalidAmountException();
    }

    void record(double amt) {
        if (count < 5) history[count++] = amt;
    }

    void deposit(double amt) {
        if (amt <= 0)
            throw InvalidAmountException();
        balance += amt;
        record(amt);
    }

    void withdraw(double amt) {
        if (amt <= 0)
            throw InvalidAmountException();
        if (amt > balance)
            throw InsufficientFundsException(balance, amt);
        balance -= amt;
        record(-amt);
    }

    double getTransaction(int index) const {
        if (index < 0 || index >= count)
            throw out_of_range("Transaction index is out of range");
        return history[index];
    }

    double getBalance() const { return balance; }
    int getCount() const { return count; }
    int getAccNo() const { return accNo; }
};

// ---------------------------------------------------------------
// Function that throws a standard exception (division by zero)
// ---------------------------------------------------------------
double average(double total, int months) {
    if (months == 0)
        throw runtime_error("Division by zero: number of months is 0");
    return total / months;
}

// ---------------------------------------------------------------
// Function that catches, logs and RETHROWS an exception
// ---------------------------------------------------------------
void performWithdrawal(Account &a, double amt) {
    Session s;                       // destroyed automatically during stack unwinding
    try {
        a.withdraw(amt);
        cout << "  Withdrawal successful. New balance: Rs. " << a.getBalance() << endl;
    }
    catch (const InsufficientFundsException &e) {
        cout << "  [Log] Failed withdrawal recorded. Rethrowing to caller..." << endl;
        throw;                       // rethrow the same exception
    }
}

// ---------------------------------------------------------------
// Input helper: throws an exception if the input is not a number
// ---------------------------------------------------------------
double readNumber(const string &msg) {
    double v;
    cout << msg;
    if (!(cin >> v)) {
        cin.clear();
        cin.ignore(10000, '\n');
        throw invalid_argument("Input is not a valid number");
    }
    return v;
}

// ---------------------------------------------------------------
// main
// ---------------------------------------------------------------
int main() {
    cout << fixed << setprecision(2);
    try {
        double bal = readNumber("Enter opening balance: ");
        Account acc(101, bal);          // may throw InvalidAmountException
        cout << "Account 101 created with balance Rs. " << acc.getBalance() << endl;

        // ---- 1. Deposit : custom exception ----
        cout << "\n--- 1. Deposit (custom exception) ---" << endl;
        try {
            double dep = readNumber("Enter deposit amount: ");
            acc.deposit(dep);
            cout << "  Deposit successful. Balance: Rs. " << acc.getBalance() << endl;
        }
        catch (const InvalidAmountException &e) {
            cout << "  [Caught] " << e.what() << endl;
        }

        // ---- 2. Withdrawal : multiple catch blocks + rethrow ----
        cout << "\n--- 2. Withdrawal (multiple catch, rethrow, stack unwinding) ---" << endl;
        try {
            double wd = readNumber("Enter withdrawal amount: ");
            performWithdrawal(acc, wd);
        }
        catch (const InsufficientFundsException &e) {
            cout << "  [Caught] " << e.what() << " (short by Rs. " << e.shortfall() << ")" << endl;
        }
        catch (const InvalidAmountException &e) {
            cout << "  [Caught] " << e.what() << endl;
        }

        // ---- 3. Division by zero : standard exception ----
        cout << "\n--- 3. Average spending (division by zero) ---" << endl;
        try {
            double total  = readNumber("Enter total spending: ");
            int months    = (int)readNumber("Enter number of months: ");
            double avg = average(total, months);   // may throw
            cout << "  Average monthly spending: Rs. " << avg << endl;
        }
        catch (const runtime_error &e) {
            cout << "  [Caught] " << e.what() << endl;
        }

        // ---- 4. Index out of range : standard exception ----
        cout << "\n--- 4. Transaction lookup (out_of_range) ---" << endl;
        try {
            int idx = (int)readNumber("Enter transaction index (0 to 4): ");
            double t = acc.getTransaction(idx);    // may throw
            cout << "  Transaction[" << idx << "] = Rs. " << t << endl;
        }
        catch (const out_of_range &e) {
            cout << "  [Caught] " << e.what() << endl;
        }

        cout << "\nFinal balance: Rs. " << acc.getBalance() << endl;
    }
    // Outer handlers: catch whatever was not handled inside
    catch (const exception &e) {
        cout << "\n[Outer catch] " << e.what() << endl;
        cout << "Program ended safely after handling the exception." << endl;
    }
    catch (...) {
        cout << "\n[Catch-all] Unknown exception occurred" << endl;
    }

    cout << "\nProgram finished normally." << endl;
    return 0;
}
