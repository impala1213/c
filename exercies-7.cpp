#include <iostream>

using namespace std;

class IntegerSet {
private:
    int     numElements,maxNumElements;
    int     *elements;
public:
    IntegerSet(int max) {
        numElements=0;
        maxNumElements=max;
        elements=new int[max];
    }

    IntegerSet(): numElements(0), maxNumElements(100) {}
    ~IntegerSet(); // to implement

    int     operator+(int);  // add an integer element, duplication is allowed
    int     operator-(int);  // remove an integer element
    int     operator[](int);  // search a value, return the number of elements matched with key
    friend ostream& operator<<(ostream&, IntegerSet&); // given as below
};

IntegerSet::~IntegerSet() {
    delete[] elements;
}

int IntegerSet::operator+(int a){
    if (numElements < maxNumElements) {
        elements[numElements++] = a;
    }
    return numElements;
}

int IntegerSet::operator-(int a){
    for (int i = 0; i < numElements; i++) {
        if (elements[i] == a) {
            for (int j = i; j < numElements - 1; j++) {
                elements[j] = elements[j + 1];
            }
            numElements--;
            break;
        }
    }
    return numElements;
}

int IntegerSet::operator[](int a){
    int count = 0;
    for (int i = 0; i < numElements; i++) {
        if (elements[i] == a) {
            count++;
        }
    }
    return count;
}

ostream& operator<<(ostream& os, IntegerSet& set) {

  for(int i=0;i<set.numElements;i++) cout<<set.elements[i]<<endl;
  return os;

}

int main() {
    IntegerSet mySet(100);
    int numLines, value;
    char op;

    cin >> numLines;
    for (int i = 0; i < numLines; i++) {
        cin >> op;
        switch (op) {
            case '+':
                cin >> value;
                cout << mySet + value << endl;
                break;
            case '-':
                cin >> value;
                cout << mySet - value << endl;
                break;
            case '?':
                cin >> value;
                cout << mySet[value] << endl;
                break;
            case '=':
                cout << mySet;
                break;
            default:
                cout << "error!" << endl;
        }
    }

    return 0;
}
