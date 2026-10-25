// Practical 10 : TEMPLATES
// Concepts: Function Template, Class Template, Template Specialization
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// ===============================================================
//                     FUNCTION TEMPLATES
// ===============================================================

// 1. Largest of two values (works for int, double, string, char ...)
template <class T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

// Explicit specialization for C-style strings: the generic version would
// compare memory addresses, so strcmp() is used instead.
template <>
const char* maxOf<const char*>(const char* a, const char* b) {
    return (strcmp(a, b) > 0) ? a : b;
}

// 2. Swap two values using references
template <class T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// 3. Bubble sort for an array of any type
template <class T>
void sortArray(T arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swapValues(arr[j], arr[j + 1]);
}

// 4. Display an array of any type
template <class T>
void displayArray(const T arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// 5. Sum of the elements of an array
template <class T>
T sumArray(const T arr[], int n) {
    T total = T();              // zero value of type T
    for (int i = 0; i < n; i++)
        total = total + arr[i];
    return total;
}

// ===============================================================
//                       CLASS TEMPLATES
// ===============================================================

// ---------------- Stack<T> ----------------
template <class T>
class Stack {
private:
    T   *data;
    int  top;
    int  capacity;
    Stack(const Stack &);              // copying disabled (Rule of Three)
    Stack& operator=(const Stack &);
public:
    Stack(int size);
    ~Stack();
    bool push(T value);
    bool pop(T &value);
    bool peek(T &value) const;
    bool isEmpty() const { return top == -1; }
    bool isFull()  const { return top == capacity - 1; }
    void display() const;
};

// member functions defined outside the class need the template header
template <class T>
Stack<T>::Stack(int size) {
    capacity = size;
    top = -1;
    data = new T[capacity];
}

template <class T>
Stack<T>::~Stack() {
    delete[] data;
}

template <class T>
bool Stack<T>::push(T value) {
    if (isFull()) return false;
    data[++top] = value;
    return true;
}

template <class T>
bool Stack<T>::pop(T &value) {
    if (isEmpty()) return false;
    value = data[top--];
    return true;
}

template <class T>
bool Stack<T>::peek(T &value) const {
    if (isEmpty()) return false;
    value = data[top];
    return true;
}

template <class T>
void Stack<T>::display() const {
    if (isEmpty()) {
        cout << "  Stack is empty" << endl;
        return;
    }
    cout << "  Stack (top -> bottom) : ";
    for (int i = top; i >= 0; i--)
        cout << data[i] << " ";
    cout << endl;
}

// ---------------- Pair<T1, T2> (two type parameters) ----------------
template <class T1, class T2>
class Pair {
private:
    T1 first;
    T2 second;
public:
    Pair(T1 a, T2 b) : first(a), second(b) {}
    T1 getFirst()  const { return first; }
    T2 getSecond() const { return second; }
    void display() const {
        cout << "  Pair = (" << first << ", " << second << ")" << endl;
    }
};

// ---------------- Calculator<T> ----------------
template <class T>
class Calculator {
private:
    T x, y;
public:
    Calculator(T a, T b) : x(a), y(b) {}
    T add() const { return x + y; }
    T sub() const { return x - y; }
    T mul() const { return x * y; }
    bool divide(T &result) const {
        if (y == T()) return false;     // division by zero
        result = x / y;
        return true;
    }
};

// ===============================================================
//   Function template that runs a Stack<T> menu for ANY type T
// ===============================================================
template <class T>
void stackMenu(const string &typeName) {
    int size, ch;
    cout << "Enter stack size: ";
    cin >> size;
    if (size <= 0) {
        cout << "Invalid size, using 5." << endl;
        size = 5;
    }
    Stack<T> st(size);
    do {
        cout << "\n  --- Stack<" << typeName << "> operations ---" << endl;
        cout << "  1. Push  2. Pop  3. Peek  4. Display  0. Back" << endl;
        cout << "  Enter choice: ";
        cin >> ch;
        T value;
        switch (ch) {
            case 1:
                cout << "  Enter value to push: ";
                cin >> value;
                if (st.push(value)) cout << "  Pushed " << value << endl;
                else cout << "  Stack overflow! Cannot push " << value << endl;
                break;
            case 2:
                if (st.pop(value)) cout << "  Popped " << value << endl;
                else cout << "  Stack underflow! Nothing to pop." << endl;
                break;
            case 3:
                if (st.peek(value)) cout << "  Top element = " << value << endl;
                else cout << "  Stack is empty." << endl;
                break;
            case 4:
                st.display();
                break;
            case 0:
                cout << "  Returning to main menu..." << endl;
                break;
            default:
                cout << "  Invalid choice!" << endl;
        }
    } while (ch != 0);
}

// ===============================================================
//                    main : menu driven program
// ===============================================================
int main() {
    int choice;
    do {
        cout << "\n===== TEMPLATES : FUNCTION AND CLASS TEMPLATES =====" << endl;
        cout << "1. Function template : Largest of two values" << endl;
        cout << "2. Function template : Swap two values" << endl;
        cout << "3. Function template : Sort and sum an array" << endl;
        cout << "4. Class template    : Stack<int>" << endl;
        cout << "5. Class template    : Stack<string>" << endl;
        cout << "6. Class template    : Pair<T1, T2>" << endl;
        cout << "7. Class template    : Calculator<T>" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: {
                int i1, i2; double d1, d2; string s1, s2;
                cout << "Enter two integers: ";
                cin >> i1 >> i2;
                cout << "Enter two decimal numbers: ";
                cin >> d1 >> d2;
                cout << "Enter two words: ";
                cin >> s1 >> s2;
                cout << "\n-- Function Template : maxOf --" << endl;
                cout << "  maxOf<int>    (" << i1 << ", " << i2 << ") = " << maxOf(i1, i2) << endl;
                cout << "  maxOf<double> (" << d1 << ", " << d2 << ") = " << maxOf(d1, d2) << endl;
                cout << "  maxOf<string> (" << s1 << ", " << s2 << ") = " << maxOf(s1, s2) << endl;
                cout << "  maxOf<const char*> specialization = "
                     << maxOf(s1.c_str(), s2.c_str()) << endl;
                break;
            }
            case 2: {
                int i1, i2; string s1, s2;
                cout << "Enter two integers: ";
                cin >> i1 >> i2;
                cout << "Enter two words: ";
                cin >> s1 >> s2;
                cout << "\n-- Function Template : swapValues --" << endl;
                cout << "  Before swap (int)    : " << i1 << ", " << i2 << endl;
                swapValues(i1, i2);
                cout << "  After  swap (int)    : " << i1 << ", " << i2 << endl;
                cout << "  Before swap (string) : " << s1 << ", " << s2 << endl;
                swapValues(s1, s2);
                cout << "  After  swap (string) : " << s1 << ", " << s2 << endl;
                break;
            }
            case 3: {
                int n;
                int ia[10]; double da[10];
                cout << "Enter number of elements (1 to 10): ";
                cin >> n;
                if (n < 1 || n > 10) {
                    cout << "Invalid size!" << endl;
                    break;
                }
                cout << "Enter " << n << " integers: ";
                for (int k = 0; k < n; k++) cin >> ia[k];
                cout << "Enter " << n << " decimal numbers: ";
                for (int k = 0; k < n; k++) cin >> da[k];
                cout << "\n-- Function Template : sortArray, displayArray, sumArray --" << endl;
                cout << "  int array before sort    : "; displayArray(ia, n);
                sortArray(ia, n);
                cout << "  int array after sort     : "; displayArray(ia, n);
                cout << "  Sum of int array         : " << sumArray(ia, n) << endl;
                cout << "  double array before sort : "; displayArray(da, n);
                sortArray(da, n);
                cout << "  double array after sort  : "; displayArray(da, n);
                cout << "  Sum of double array      : " << sumArray(da, n) << endl;
                break;
            }
            case 4:
                cout << "\n-- Class Template : Stack<int> --" << endl;
                stackMenu<int>("int");
                break;
            case 5:
                cout << "\n-- Class Template : Stack<string> --" << endl;
                stackMenu<string>("string");
                break;
            case 6: {
                int id; string name, subject; double marks;
                cout << "Enter id and name: ";
                cin >> id >> name;
                cout << "Enter subject and marks: ";
                cin >> subject >> marks;
                cout << "\n-- Class Template : Pair<T1, T2> --" << endl;
                Pair<int, string> p1(id, name);
                Pair<string, double> p2(subject, marks);
                cout << "  Pair<int, string>   :"; p1.display();
                cout << "  Pair<string, double>:"; p2.display();
                break;
            }
            case 7: {
                int a, b; double x, y;
                cout << "Enter two integers: ";
                cin >> a >> b;
                cout << "Enter two decimal numbers: ";
                cin >> x >> y;
                cout << "\n-- Class Template : Calculator<T> --" << endl;
                Calculator<int> ci(a, b);
                cout << "  Calculator<int>    : add=" << ci.add() << ", sub=" << ci.sub()
                     << ", mul=" << ci.mul() << ", div=";
                int ri;
                if (ci.divide(ri)) cout << ri << endl;
                else cout << "Error (division by zero)" << endl;
                Calculator<double> cd(x, y);
                cout << "  Calculator<double> : add=" << cd.add() << ", sub=" << cd.sub()
                     << ", mul=" << cd.mul() << ", div=";
                double rd;
                if (cd.divide(rd)) cout << rd << endl;
                else cout << "Error (division by zero)" << endl;
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
