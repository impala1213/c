#include <iostream>
using namespace std;

class node {
public:
    int value;
    node* link;

    node(int val) {
        value = val;
        link = nullptr;
    }
};

class linkedlist {
private:
    node* start;

public:
    linkedlist() {
        start = nullptr;
    }

void insert(int pos, int val) {
    if (pos < 0 || pos > 99) {
        cout << "err_code=100" << endl;
        return;
    }

    int length = 0;
    node* current = start;
    while (current != nullptr) {
        length++;
        current = current->link;
    }

    if (length >= 99 && pos != length) {
        cout << "err_code=100" << endl;
        return;
    }

    node* newnode = new node(val);

    if (pos == 0) {
        newnode->link = start;
        start = newnode;
        printlist();
        return;
    }

    if (pos == 99) {
        if (start == nullptr) {
            start = newnode;
            printlist();
            return;
        }

        current = start;
        while (current->link != nullptr) {
            current = current->link;
        }
        current->link = newnode;
        printlist();
        return;
    }

    current = start;
    int counter = 0;
    while (counter < pos - 1 && current != nullptr) {
        current = current->link;
        counter++;
    }

    if (current == nullptr) {
        cout << "err_code=100" << endl;
        delete newnode;
        return;
    }

    newnode->link = current->link;
    current->link = newnode;
    printlist();
}


    void deletenode(int val) {
        if (start == nullptr) {
            cout << "err_code=101" << endl;
            return;
        }

        if (start->value == val) {
            node* temp = start;
            start = start->link;
            delete temp;
            printlist();
            return;
        }

        node* current = start;
        while (current->link != nullptr && current->link->value != val) {
            current = current->link;
        }

        if (current->link == nullptr) {
            cout << "err_code=101" << endl;
            return;
        }

        node* temp = current->link;
        current->link = temp->link;
        delete temp;
        printlist();
    }

    void reverse() {
        if (start == nullptr) {
            cout << "err_code=102" << endl;
            return;
        }

        node *prev = nullptr, *current = start, *next = nullptr;
        while (current != nullptr) {
            next = current->link;
            current->link = prev;
            prev = current;
            current = next;
        }
        start = prev;
        printlist();
    }

    void find(int val) {
        if (start == nullptr) {
            cout << "err_code=103" << endl;
            return;
        }

        node* current = start;
        int idx = 0;
        while (current != nullptr) {
            if (current->value == val) {
                cout << idx << endl;
                return;
            }
            current = current->link;
            idx++;
        }
        cout << "err_code=103" << endl;
    }

 void sublist(int begin, int finish) {
    if (start == nullptr || begin < 0 || begin > finish) {
        cout << "err_code=104" << endl;
        return;
    }

    int length = 0;
    node* current = start;
    while (current != nullptr) {
        length++;
        current = current->link;
    }
    if (begin == 99) {
        begin = length - 1;
    }


    if (finish == 99) {
        finish = length - 1;
    }

    current = start;
    int idx = 0;

    while (idx < begin && current != nullptr) {
        current = current->link;
        idx++;
    }

    if (current == nullptr) {
        cout << "err_code=104" << endl;
        return;
    }

    string result = "";
    while (idx <= finish && current != nullptr) {
        result += to_string(current->value);
        current = current->link;
        if (idx < finish && current != nullptr) {
            result += " -> ";
        }
        idx++;
    }

    if (idx <= finish) {
        cout << "err_code=104" << endl;
        return;
    }

    cout << result << " -> NULL" << endl;
}


    void count(int val) {
        int freq = 0;
        node* current = start;

        while (current != nullptr) {
            if (current->value == val) {
                freq++;
            }
            current = current->link;
        }

        cout << freq << endl;
    }

    void sort() {
        if (start == nullptr) {
            cout << "err_code=105" << endl;
            return;
        }

        bool swapped;
        node* current;
        node* last = nullptr;

        do {
            swapped = false;
            current = start;

            while (current->link != last) {
                if (current->value > current->link->value) {
                    int temp = current->value;
                    current->value = current->link->value;
                    current->link->value = temp;
                    swapped = true;
                }
                current = current->link;
            }
            last = current;
        } while (swapped);

        printlist();
    }

    void printlist() {
        if (start == nullptr) {
            cout << "NULL" << endl;
            return;
        }

        node* current = start;
        while (current != nullptr) {
            cout << current->value;
            if (current->link != nullptr) {
                cout << " -> ";
            }
            current = current->link;
        }
        cout << " -> NULL" << endl;
    }
};

int main() {
    linkedlist lst;
    char cmd;
    int pos, val, begin, finish;

    while (cin >> cmd) {
        switch (cmd) {
            case 'I':
                cin.ignore();
                cin >> pos;
                cin.ignore();
                cin >> val;
                lst.insert(pos, val);
                break;

            case 'D':
                cin.ignore();
                cin >> val;
                lst.deletenode(val);
                break;

            case 'R':
                lst.reverse();
                break;

            case 'F':
                cin.ignore();
                cin >> val;
                lst.find(val);
                break;

            case 'S':
                cin.ignore();
                cin >> begin;
                cin.ignore();
                cin >> finish;
                lst.sublist(begin, finish);
                break;

            case 'C':
                cin.ignore();
                cin >> val;
                lst.count(val);
                break;

            case 'T':
                lst.sort();
                break;

            default:

                break;
        }
    }

    return 0;
}
