#include <iostream>
using namespace std;

template<class T>
class vector {
    int num;
public:
    T *v;
    vector(int);
    ~vector();
    vector(T *b);
    void show();
    T minimum();
};

template<class T>
vector<T>::vector(int n): num(n) {
    v=(T *) new T[n];
}

template<class T>
vector<T>::~vector() {
    delete[] v;
}

template<class T>
T vector<T>::minimum() {
    if (num == 0) {
        return 0;
    }
    T min_value = v[0];
    for (int i = 1; i < num; ++i) {
        if (v[i] < min_value) {
            min_value = v[i];
        }
    }
    return min_value;
}

template<class T>
void vector<T>::show() {
    for (int i = 0; i < num; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    int number;
    cin >> number;
    vector<int> v1(number);

    for (int i = 0; i < number; i++) cin >> v1.v[i];

    cout << v1.minimum() << "\n";
    v1.show();

    cin >> number;
    vector<float> v2(number);

    for (int i = 0; i < number; i++) cin >> v2.v[i];

    cout << v2.minimum() << "\n";
    v2.show();

    return 0;
}
