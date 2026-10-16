#include <iostream>
using namespace std;

// Swap using pointers
void swapByPointer(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Swap using references
void swapByReference(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x = 10, y = 20;

    int *ptr = &x;   // pointer storing address of x
    int &ref = x;    // reference (alias) of x

    cout << "--- Pointer and Reference Basics ---" << endl;
    cout << "Value of x            : " << x << endl;
    cout << "Address of x (&x)     : " << &x << endl;
    cout << "Value of ptr (address): " << ptr << endl;
    cout << "Value at ptr (*ptr)   : " << *ptr << endl;
    cout << "Value of ref          : " << ref << endl;

    *ptr = 50;
    cout << "\nAfter *ptr = 50, x = " << x << endl;
    ref = 75;
    cout << "After ref = 75, x = " << x << endl;

    x = 10;
    cout << "\nBefore swap: x = " << x << ", y = " << y << endl;
    swapByPointer(&x, &y);
    cout << "After swap using pointers: x = " << x << ", y = " << y << endl;
    swapByReference(x, y);
    cout << "After swap using references: x = " << x << ", y = " << y << endl;

    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;
    cout << "\nArray elements using pointer: ";
    for (int i = 0; i < 5; i++)
        cout << *(p + i) << " ";
    cout << endl;

    return 0;
}



2nd code PART B

#include <iostream>
using namespace std;

int main()
{
    // 1. Dynamic memory for a single variable
    int *p = new int;
    *p = 25;
    cout << "--- Single Variable ---" << endl;
    cout << "Value stored dynamically: " << *p << endl;
    delete p;
    p = NULL;

    // 2. Dynamic memory for an array
    int n;
    cout << "\nEnter number of elements: ";
    cin >> n;

    int *arr = new int[n];

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    cout << "\n--- Array Details ---" << endl;
    cout << "Elements: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\nSum     : " << sum << endl;
    cout << "Average : " << (float)sum / n << endl;

    delete[] arr;
    arr = NULL;
    cout << "\nMemory released using delete[]." << endl;

    return 0;
}