#include <iostream>
using namespace std;

class Complex
{
    int a;
    int b;

public:
    // Default 
    Complex()
    {
        a= 0;
        b= 0;
    }

    //Parameterized 
    Complex(int x, int y)
    {
        a= x;
        b =y;
    }

    //Operator Overloading
    Complex operator+(Complex obj)
    {
        Complex result;

        result.a =a + obj.a;
        result.b =b + obj.b;

        return result;
    }


    void display()
    {
        if (b>= 0)
            cout <<a << " + " << b << "i";
        else
            cout<< a<< " - " <<-b << "i";
    }
};

int main()
{
    int x1, y1, x2, y2;


    cout << "Enter real and imaginary of first complex no.: ";
    cin >> x1 >> y1;

    cout << "Enter real and imaginary of second complex no.: ";
    cin >> x2 >> y2;

    Complex num1(x1, y1);
    Complex num2(x2, y2);
    Complex result;
    result = num1 + num2;

    cout << "\nFirst Complex Number: ";
    num1.display();

    cout << "\nSecond Complex Number: ";
    num2.display();

    cout << "\nAddition: ";
    result.display();

    return 0;
}
