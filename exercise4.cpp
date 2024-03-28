#include <iostream>
using namespace std;

class Point {
private:
    float x, y;
public:
    Point();
    Point(const Point &);
    Point operator+(const Point &B);
    Point operator+(float op);
    friend ostream& operator<<(ostream&, const Point&);
    friend istream& operator>>(istream&, Point&);
};

ostream& operator<<(ostream& os, const Point& p) {
    os << p.x << " " << p.y << "\n";
    return os;
}


istream& operator>>(istream& is, Point& p) {
    is >> p.x >> p.y;
    return is;
}

Point::Point(const Point & rhs) {
    x = rhs.x; y = rhs.y;
}

Point::Point() : x(0), y(0) {
}

Point Point::operator+(const Point &op) {
    Point temp;
    temp.x = x + op.x;
    temp.y = y + op.y;
    return temp;
}

Point Point::operator+(float op) {
    Point temp;
    temp.x = x + op;
    temp.y = y + op;
    return temp;
}

int main() {
    Point A, B, C;
    float D;
    cin >> A >> B;
    C = A + B;
    cin >> D;
    cout << C;
    C = C + D;
    cout << C;
    return 0;
}
