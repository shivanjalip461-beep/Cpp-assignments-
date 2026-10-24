// Polymorphism: Shape Area Calculator
// Concepts: Compile-time polymorphism (function overloading, operator overloading)
//           Run-time polymorphism (virtual function, pure virtual function,
//           abstract class, virtual destructor, base class pointer)
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iomanip>
using namespace std;

const double PI = 3.14159265;

// ---------------------------------------------------------------
// Abstract base class: Shape
// ---------------------------------------------------------------
class Shape {
protected:
    string name;
public:
    Shape(string n) : name(n) {}

    // Pure virtual functions -> Shape is an abstract class
    virtual double area() const = 0;
    virtual double perimeter() const = 0;

    // Virtual function: derived classes override it (run-time polymorphism)
    virtual void display() const {
        cout << "  Shape     : " << name << endl;
        cout << "  Area      : " << area() << endl;
        cout << "  Perimeter : " << perimeter() << endl;
    }

    // Operator overloading (compile-time polymorphism): compare by area
    bool operator>(const Shape &other) const {
        return area() > other.area();
    }

    // Virtual destructor: derived destructor runs when deleting via base pointer
    virtual ~Shape() {
        cout << "  [Destructor] " << name << " destroyed" << endl;
    }
};

// ---------------------------------------------------------------
// Derived class: Circle
// ---------------------------------------------------------------
class Circle : public Shape {
    double r;
public:
    Circle(double r) : Shape("Circle"), r(r) {}
    double area() const override { return PI * r * r; }
    double perimeter() const override { return 2 * PI * r; }
    void display() const override {
        cout << "  Radius    : " << r << endl;
        Shape::display();
    }
};

// ---------------------------------------------------------------
// Derived class: Rectangle
// ---------------------------------------------------------------
class Rectangle : public Shape {
    double l, b;
public:
    Rectangle(double l, double b) : Shape("Rectangle"), l(l), b(b) {}
    double area() const override { return l * b; }
    double perimeter() const override { return 2 * (l + b); }
    void display() const override {
        cout << "  Length    : " << l << ", Breadth : " << b << endl;
        Shape::display();
    }
};

// ---------------------------------------------------------------
// Derived class: Triangle (three sides, area by Heron's formula)
// ---------------------------------------------------------------
class Triangle : public Shape {
    double a, b, c;
public:
    Triangle(double a, double b, double c) : Shape("Triangle"), a(a), b(b), c(c) {}
    double area() const override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    double perimeter() const override { return a + b + c; }
    void display() const override {
        cout << "  Sides     : " << a << ", " << b << ", " << c << endl;
        Shape::display();
    }
};

// ---------------------------------------------------------------
// Function overloading (compile-time polymorphism)
// Same function name, different number of parameters
// ---------------------------------------------------------------
class AreaCalculator {
public:
    double calc(double r) { return PI * r * r; }                 // circle
    double calc(double l, double b) { return l * b; }            // rectangle
    double calc(double a, double b, double c) {                  // triangle
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

// ---------------------------------------------------------------
// Input helper: keeps asking until a positive number is entered
// ---------------------------------------------------------------
double readPositive(const string &msg) {
    double v;
    while (true) {
        cout << msg;
        if (!(cin >> v)) {
            cout << "Invalid input. Program stopped." << endl;
            exit(1);
        }
        if (v > 0) return v;
        cout << "  Value must be greater than 0. Try again." << endl;
    }
}

// ---------------------------------------------------------------
// main
// ---------------------------------------------------------------
int main() {
    double r, l, b, s1, s2, s3;

    r = readPositive("Enter radius of circle: ");
    l = readPositive("Enter length of rectangle: ");
    b = readPositive("Enter breadth of rectangle: ");

    // Triangle inequality must hold, otherwise ask again
    while (true) {
        s1 = readPositive("Enter side 1 of triangle: ");
        s2 = readPositive("Enter side 2 of triangle: ");
        s3 = readPositive("Enter side 3 of triangle: ");
        if (s1 + s2 > s3 && s2 + s3 > s1 && s1 + s3 > s2) break;
        cout << "  These sides cannot form a triangle. Enter again." << endl;
    }

    cout << fixed << setprecision(2);

    // ---- Compile-time polymorphism: function overloading ----
    AreaCalculator calc;
    cout << "\n--- Compile-time Polymorphism (Function Overloading) ---" << endl;
    cout << "  calc(r)        -> Circle area    : " << calc.calc(r) << endl;
    cout << "  calc(l, b)     -> Rectangle area : " << calc.calc(l, b) << endl;
    cout << "  calc(a, b, c)  -> Triangle area  : " << calc.calc(s1, s2, s3) << endl;

    // ---- Run-time polymorphism: base class pointers ----
    Shape *shapes[3];
    shapes[0] = new Circle(r);
    shapes[1] = new Rectangle(l, b);
    shapes[2] = new Triangle(s1, s2, s3);

    cout << "\n--- Run-time Polymorphism (Virtual Functions) ---" << endl;
    double total = 0;
    for (int i = 0; i < 3; i++) {
        cout << "Shape " << i + 1 << ":" << endl;
        shapes[i]->display();          // correct version called at run time
        total += shapes[i]->area();
    }
    cout << "\n  Total area of all shapes: " << total << endl;

    // ---- Operator overloading: find the largest shape ----
    cout << "\n--- Operator Overloading (operator >) ---" << endl;
    Shape *largest = shapes[0];
    for (int i = 1; i < 3; i++)
        if (*shapes[i] > *largest)
            largest = shapes[i];
    cout << "Shape with the largest area:" << endl;
    largest->display();

    // ---- Virtual destructor ----
    cout << "\n--- Virtual Destructor ---" << endl;
    for (int i = 0; i < 3; i++)
        delete shapes[i];

    return 0;
}
