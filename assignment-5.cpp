#include <iostream>
using namespace std;

class Complex {
private:
    int real;
    int im;

public:
    Complex(int r, int i) : real(r), im(i) {
        cout << "Constructor " << real << " " << im << endl;
    }

    // 복사 생성자
    Complex(const Complex& c) : real(c.real), im(c.im) {
        cout << "Copy" << endl;
    }

    friend Complex operator+(const Complex& a, const Complex& b) {
        //Complex temp(a.real + b.real, a.im + b.im);
        cout << "+ " << a.real + b.real << " " << a.im+b.im << endl;
    }
};

int main() {
    int real1, im1, real2, im2;

    cin >> real1 >> im1;
    cin >> real2 >> im2;
    Complex c1(real1, im1);
    Complex c2(real2, im2);
    Complex c0(c1);
    Complex c3 = c1 + c2;

    return 0;
}
