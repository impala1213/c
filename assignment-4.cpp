#include <iostream>
using namespace std;

class Complex {
private:
    float real;
    float im;
public:

    Complex(float r = 0, float i = 0) : real(r), im(i) {}


    Complex operator+(const Complex &B) const {
        return Complex(real + B.real, im + B.im);
    }


    Complex operator*(const Complex &B) const {
        return Complex(real * B.real, B.im * im);
    }

    Complex operator+(float op) const {
        return Complex(real + op, im);
    }

    Complex operator*(float op) const {
        return Complex(real * op, im * op);
    }

    friend ostream& operator<<(ostream& os, const Complex& p) {
        os << p.real << " " << p.im << endl;
        return os;
    }

    friend istream& operator>>(istream& is, Complex& p) {
        is >> p.real >> p.im;
        return is;
    }
};

int main() {
    Complex A, B, C;
    float D;
    cin >> A; cin >> B;
    C = A + B;
    cout << C;
    C = A * B;
    cout << C;
    cin >> D;
    C = C * D;
    cout << C;
    return 0;
}
