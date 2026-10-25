// Practical 12 : TYPE CASTING AND CASTING OPERATORS
// Concepts: Implicit conversion, C-style/functional cast, static_cast,
//           dynamic_cast, const_cast, reinterpret_cast, user-defined conversion
#include <iostream>
#include <string>
#include <typeinfo>
#include <cstddef>
using namespace std;

// ---------------------------------------------------------------
// Classes used for static_cast / dynamic_cast demonstration
// ---------------------------------------------------------------
class Shape {                              // polymorphic base class
public:
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const { return 3.14159 * radius * radius; }
    double getRadius() const { return radius; }      // Circle only
};

class Rectangle : public Shape {
private:
    double length, width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    double area() const { return length * width; }
    double getLength() const { return length; }      // Rectangle only
    double getWidth() const { return width; }
};

// ---------------------------------------------------------------
// Classes used for user-defined conversions
// ---------------------------------------------------------------
class Celsius {
private:
    double temp;
public:
    Celsius(double t = 0) : temp(t) {}                // basic -> class
    operator double() const { return temp; }          // class -> basic
    double get() const { return temp; }
};

class Fahrenheit {
private:
    double temp;
public:
    Fahrenheit(const Celsius &c) : temp(c.get() * 9.0 / 5.0 + 32.0) {}  // class -> class
    double get() const { return temp; }
};

// legacy function that takes a NON-const pointer (used by const_cast demo)
void addTen(int *p) {
    *p = *p + 10;
}

enum Level { LOW = 1, MEDIUM = 5, HIGH = 10 };

// ---------------------------------------------------------------
// main : menu driven program
// ---------------------------------------------------------------
int main() {
    int choice;
    do {
        cout << "\n===== TYPE CASTING AND CASTING OPERATORS =====" << endl;
        cout << "1. Implicit type conversion" << endl;
        cout << "2. Explicit casting (C-style and functional)" << endl;
        cout << "3. static_cast" << endl;
        cout << "4. dynamic_cast" << endl;
        cout << "5. const_cast" << endl;
        cout << "6. reinterpret_cast" << endl;
        cout << "7. User-defined conversion (class)" << endl;
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
                int a; double b; char ch;
                cout << "Enter an integer, a decimal number and a character: ";
                cin >> a >> b >> ch;
                cout << "\n-- Implicit Type Conversion --" << endl;
                cout << "  int + double      : " << a << " + " << b << " = " << (a + b)
                     << "  (int promoted to double)" << endl;
                cout << "  char + int        : '" << ch << "' + " << a << " = " << (ch + a)
                     << "  (char promoted to int, ASCII " << (int)ch << ")" << endl;
                int n = b;                       // double -> int (narrowing)
                cout << "  int n = " << b << "     : n = " << n
                     << "  (fractional part lost)" << endl;
                cout << "  " << a << " / 2           : " << (a / 2)
                     << "  (integer division)" << endl;
                cout << "  " << a << " / 2.0         : " << (a / 2.0)
                     << "  (int converted to double)" << endl;
                break;
            }
            case 2: {
                int total, subjects; double d;
                cout << "Enter total marks, number of subjects and a decimal number: ";
                cin >> total >> subjects >> d;
                if (subjects == 0) {
                    cout << "Number of subjects cannot be zero!" << endl;
                    break;
                }
                cout << "\n-- Explicit Casting --" << endl;
                cout << "  Without cast  total / subjects          = "
                     << (total / subjects) << "  (integer division)" << endl;
                cout << "  C-style       (float)total / subjects   = "
                     << (float)total / subjects << endl;
                cout << "  Functional    float(total) / subjects   = "
                     << float(total) / subjects << endl;
                cout << "  C-style       (int)" << d << "                  = "
                     << (int)d << "  (truncated, not rounded)" << endl;
                break;
            }
            case 3: {
                int a, b; double d; char ch;
                cout << "Enter two integers, a decimal number and a character: ";
                cin >> a >> b >> d >> ch;
                if (b == 0) {
                    cout << "Second integer cannot be zero!" << endl;
                    break;
                }
                cout << "\n-- static_cast --" << endl;
                cout << "  static_cast<double>(a) / b   = "
                     << static_cast<double>(a) / b << endl;
                cout << "  static_cast<int>(d)          = "
                     << static_cast<int>(d) << endl;
                cout << "  static_cast<int>(ch)         = "
                     << static_cast<int>(ch) << "  (ASCII code)" << endl;
                cout << "  static_cast<char>(ch + 1)    = "
                     << static_cast<char>(ch + 1) << "  (next character)" << endl;
                Level lv = static_cast<Level>(5);
                cout << "  static_cast<Level>(5)        = " << (lv == MEDIUM ? "MEDIUM" : "?")
                     << ", static_cast<int>(HIGH) = " << static_cast<int>(HIGH) << endl;
                void *vp = static_cast<void*>(&a);
                int  *ip = static_cast<int*>(vp);
                cout << "  int* -> void* -> int*        : value = " << *ip << endl;
                Circle c(2.0);
                Shape *sp = static_cast<Shape*>(&c);           // upcast
                cout << "  Upcast Circle* -> Shape*     : area = " << sp->area() << endl;
                break;
            }
            case 4: {
                int type;
                cout << "Enter shape (1 = Circle, 2 = Rectangle): ";
                cin >> type;
                Shape *sp = NULL;
                if (type == 1) {
                    double r;
                    cout << "Enter radius: ";
                    cin >> r;
                    sp = new Circle(r);
                } else if (type == 2) {
                    double l, w;
                    cout << "Enter length and width: ";
                    cin >> l >> w;
                    sp = new Rectangle(l, w);
                } else {
                    cout << "Invalid shape!" << endl;
                    break;
                }
                cout << "\n-- dynamic_cast (Shape* downcast at run time) --" << endl;
                cout << "  Area through Shape* = " << sp->area() << endl;

                Circle *cp = dynamic_cast<Circle*>(sp);
                if (cp != NULL)
                    cout << "  dynamic_cast<Circle*>    : SUCCESS, radius = " << cp->getRadius() << endl;
                else
                    cout << "  dynamic_cast<Circle*>    : FAILED (NULL returned)" << endl;

                Rectangle *rp = dynamic_cast<Rectangle*>(sp);
                if (rp != NULL)
                    cout << "  dynamic_cast<Rectangle*> : SUCCESS, length = " << rp->getLength()
                         << ", width = " << rp->getWidth() << endl;
                else
                    cout << "  dynamic_cast<Rectangle*> : FAILED (NULL returned)" << endl;

                try {
                    Circle &cr = dynamic_cast<Circle&>(*sp);   // reference form
                    cout << "  dynamic_cast<Circle&>    : SUCCESS, radius = " << cr.getRadius() << endl;
                } catch (bad_cast &) {
                    cout << "  dynamic_cast<Circle&>    : FAILED (std::bad_cast thrown)" << endl;
                }
                delete sp;
                break;
            }
            case 5: {
                int x, y;
                cout << "Enter an integer and a new value: ";
                cin >> x >> y;
                cout << "\n-- const_cast --" << endl;
                const int *cp = &x;              // pointer to const: *cp = y is not allowed
                cout << "  Original value of x               = " << x << endl;
                int *p = const_cast<int*>(cp);   // constness removed
                addTen(p);                       // legacy function needs int*
                cout << "  After addTen(const_cast<int*>(cp)) = " << x << endl;
                *p = y;
                cout << "  After *p = " << y << " through const_cast  = " << x << endl;
                cout << "  Note: this is safe only because x itself is NOT declared const." << endl;
                break;
            }
            case 6: {
                int n;
                cout << "Enter an integer: ";
                cin >> n;
                cout << "\n-- reinterpret_cast --" << endl;
                unsigned char *bytes = reinterpret_cast<unsigned char*>(&n);
                cout << "  Bytes of " << n << " in memory (lowest address first, hex): ";
                cout << hex;
                for (size_t i = 0; i < sizeof(int); i++)
                    cout << (int)bytes[i] << " ";
                cout << dec << endl;
                size_t addr = reinterpret_cast<size_t>(&n);      // pointer -> integer
                int *back = reinterpret_cast<int*>(addr);        // integer -> pointer
                cout << "  Pointer -> integer -> pointer : "
                     << (back == &n ? "same address recovered" : "different address")
                     << ", value = " << *back << endl;
                cout << "  Note: the byte order shown depends on the machine (endianness)." << endl;
                break;
            }
            case 7: {
                double t;
                cout << "Enter temperature in Celsius: ";
                cin >> t;
                cout << "\n-- User-defined Conversion --" << endl;
                Celsius c = t;                   // basic type -> class (constructor)
                double d = c;                    // class -> basic type (conversion operator)
                Fahrenheit f = c;                // class -> class (constructor)
                cout << "  double -> Celsius (constructor)        : " << c.get() << " C" << endl;
                cout << "  Celsius -> double (conversion operator): " << d << endl;
                cout << "  Celsius -> Fahrenheit (class to class) : " << f.get() << " F" << endl;
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
