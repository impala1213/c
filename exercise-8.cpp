#include <iostream>
#define PI  3.14

using namespace std;

float Abs(float x) {
    return x < 0 ? -x : x;
}

class Geom {
protected:
    int type;
public:
    enum {RECT = 'R', CIRCLE = 'C', SQUARE = 'S', POINT = 'P'};
    Geom(int t): type(t) {}
    virtual float area()=0;
};

class Point: public Geom {
    float a, b;
public:
    Point(float x, float y): Geom(POINT), a(x), b(y) {}
    float getA() const { return a; }
    float getB() const { return b; }
    float area() { return 0.0; }
};

class Circle: public Geom {
    Point center;
    float radius;
public:
    Circle(float x, float y, float r):
        Geom(CIRCLE), center(x,y), radius(r) {}
    float area() { return PI*radius*radius; }
};

class Rectangle: public Geom {
    Point p1;
    Point p2;
public:
    Rectangle(float x1, float y1, float x2, float y2):
    Geom(RECT), p1(x1, y1), p2(x2, y2) {}
    float area() {
        return Abs((p2.getA() - p1.getA()) * (p2.getB() - p1.getB()));
    }
};

class Square: public Geom {
    Point p;
    float side;
public:
    Square(float x, float y, float s): Geom(SQUARE), p(x, y), side(s) {}
    float area() {
        return side * side;
    }
};

int main() {
    int numGeom;
    cin >> numGeom;
    Geom* geom;
    for(int i = 0; i < numGeom; i++) {
        char type;
        cin >> type;
        geom = nullptr;
        switch(type) {
            case 'C': {
                float x, y, r;
                cin >> x >> y >> r;
                geom = new Circle(x, y, r);
                break;
            }
            case 'R': {
                float x1, y1, x2, y2;
                cin >> x1 >> y1 >> x2 >> y2;
                geom = new Rectangle(x1, y1, x2, y2);
                break;
            }
            case 'S': {
                float x, y, side;
                cin >> x >> y >> side;
                geom = new Square(x, y, side);
                break;
            }
            case 'P': {
                float x, y;
                cin >> x >> y;
                geom = new Point(x, y);
                break;
            }
            default:
                return 1;
        }
        if (geom != nullptr) {
            cout << geom->area() << endl;
            delete geom;
        }
    }

    return 0;
}
