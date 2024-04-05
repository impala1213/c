#include <iostream>
using namespace std;

class Complex {
private:
    int real;
    int im;

public:
    Complex(int r, int i, bool output = true) : real(r), im(i) {
        if (output) {
            cout << "Constructor " << real << " " << im << endl;
        }
    }

    Complex(const Complex& c) : real(c.real), im(c.im) {
        cout << "Copy" << endl;
    }

    friend Complex operator+(const Complex& c1, const Complex& c2) {
        Complex temp(c1.real + c2.real, c1.im + c2.im, false);
        cout << "+ " << temp.real << " " << temp.im << endl;
        return temp;
    }
};

int main() {
    int real1, im1, real2, im2;
    cin >> real1 >> im1 >> real2 >> im2;
    Complex c1(real1, im1);
    Complex c2(real2, im2);
    Complex c0(c1);
    Complex c3 = c1 + c2;

    return 0;
}
