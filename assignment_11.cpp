// Standard Template Library: list and vector containers
// a) list as a container   b) vector as a container
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

// ---------------- display helpers (use iterators) ----------------
void show(const list<int> &l) {
    if (l.empty()) { cout << "  List is empty" << endl; return; }
    cout << "  List : ";
    for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
        cout << *it << " ";
    cout << endl;
}
void show(const vector<int> &v) {
    if (v.empty()) { cout << "  Vector is empty" << endl; return; }
    cout << "  Vector : ";
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

// ---------------- Part (a): list ----------------
void listMenu() {
    list<int> l;
    int ch, x, pos;
    do {
        cout << "\n--- LIST MENU ---\n"
             << "1.Insert at end   2.Insert at front   3.Insert at position\n"
             << "4.Delete front    5.Delete back       6.Remove a value\n"
             << "7.Sort            8.Reverse           9.Remove duplicates\n"
             << "10.Display        11.Size             0.Back\n"
             << "Enter choice: ";
        cin >> ch;
        switch (ch) {
        case 1: cout << "Enter value: "; cin >> x; l.push_back(x); show(l); break;
        case 2: cout << "Enter value: "; cin >> x; l.push_front(x); show(l); break;
        case 3: {
            cout << "Enter position (0 to " << l.size() << ") and value: ";
            cin >> pos >> x;
            if (pos < 0 || pos > (int)l.size()) { cout << "  Invalid position" << endl; break; }
            list<int>::iterator it = l.begin();
            advance(it, pos);
            l.insert(it, x);
            show(l); break;
        }
        case 4: if (l.empty()) cout << "  List is empty" << endl;
                else { cout << "  Deleted " << l.front() << endl; l.pop_front(); show(l); }
                break;
        case 5: if (l.empty()) cout << "  List is empty" << endl;
                else { cout << "  Deleted " << l.back() << endl; l.pop_back(); show(l); }
                break;
        case 6: cout << "Enter value to remove: "; cin >> x;
                { size_t before = l.size(); l.remove(x);
                  if (l.size() == before) cout << "  Value not found" << endl;
                  else cout << "  Removed " << before - l.size() << " occurrence(s)" << endl; }
                show(l); break;
        case 7: l.sort(); cout << "  Sorted (ascending)" << endl; show(l); break;
        case 8: l.reverse(); cout << "  Reversed" << endl; show(l); break;
        case 9: l.sort(); l.unique(); cout << "  Duplicates removed" << endl; show(l); break;
        case 10: show(l); break;
        case 11: cout << "  Size = " << l.size() << endl; break;
        case 0: break;
        default: cout << "  Invalid choice" << endl;
        }
    } while (ch != 0);
}

// ---------------- Part (b): vector ----------------
void vectorMenu() {
    vector<int> v;
    int ch, x, pos;
    do {
        cout << "\n--- VECTOR MENU ---\n"
             << "1.Insert at end    2.Insert at position   3.Erase at position\n"
             << "4.Search a value   5.Sort ascending       6.Sort descending\n"
             << "7.Sum/Max/Min      8.Display              9.Size and capacity\n"
             << "10.Delete last     0.Back\n"
             << "Enter choice: ";
        cin >> ch;
        switch (ch) {
        case 1: cout << "Enter value: "; cin >> x; v.push_back(x); show(v); break;
        case 2: {
            cout << "Enter position (0 to " << v.size() << ") and value: ";
            cin >> pos >> x;
            if (pos < 0 || pos > (int)v.size()) { cout << "  Invalid position" << endl; break; }
            v.insert(v.begin() + pos, x); show(v); break;
        }
        case 3: {
            if (v.empty()) { cout << "  Vector is empty" << endl; break; }
            cout << "Enter position (0 to " << (int)v.size() - 1 << "): "; cin >> pos;
            if (pos < 0 || pos >= (int)v.size()) { cout << "  Invalid position" << endl; break; }
            v.erase(v.begin() + pos); show(v); break;
        }
        case 4: {
            cout << "Enter value to search: "; cin >> x;
            vector<int>::iterator it = find(v.begin(), v.end(), x);
            if (it == v.end()) cout << "  " << x << " not found" << endl;
            else cout << "  " << x << " found at index " << it - v.begin() << endl;
            break;
        }
        case 5: sort(v.begin(), v.end()); cout << "  Sorted (ascending)" << endl; show(v); break;
        case 6: sort(v.begin(), v.end(), greater<int>()); cout << "  Sorted (descending)" << endl; show(v); break;
        case 7:
            if (v.empty()) { cout << "  Vector is empty" << endl; break; }
            cout << "  Sum = " << accumulate(v.begin(), v.end(), 0)
                 << ", Max = " << *max_element(v.begin(), v.end())
                 << ", Min = " << *min_element(v.begin(), v.end()) << endl;
            break;
        case 8: show(v); break;
        case 9: cout << "  Size = " << v.size() << ", Capacity = " << v.capacity() << endl; break;
        case 10: if (v.empty()) cout << "  Vector is empty" << endl;
                 else { v.pop_back(); cout << "  Last element deleted" << endl; show(v); }
                 break;
        case 0: break;
        default: cout << "  Invalid choice" << endl;
        }
    } while (ch != 0);
}

int main() {
    int ch;
    do {
        cout << "\n===== STL CONTAINERS =====\n"
             << "1. List container\n2. Vector container\n0. Exit\nEnter choice: ";
        if (!(cin >> ch)) { cout << "Invalid input. Exiting." << endl; break; }
        switch (ch) {
        case 1: listMenu(); break;
        case 2: vectorMenu(); break;
        case 0: cout << "Program finished." << endl; break;
        default: cout << "Invalid choice" << endl;
        }
    } while (ch != 0);
    return 0;
}
