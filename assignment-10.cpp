#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

#define PI 3.14

using namespace std;

enum ShapeType { POINT, CIRCLE, RECTANGLE, SQUARE };

class Geometry {
    int type;
public:
    Geometry(int t) : type(t) {}
    virtual ~Geometry() {}
    virtual float area() const = 0;
    friend bool operator==(const Geometry& a, const Geometry& b) { return a.area() == b.area(); }
    friend bool operator<(const Geometry& a, const Geometry& b) { return a.area() < b.area(); }
    friend bool operator>(const Geometry& a, const Geometry& b) { return !(a < b) && !(a == b); }
};

class Point : public Geometry {
    float a, b;
public:
    Point(float x, float y) : Geometry(POINT), a(x), b(y) {}
    Point() : Geometry(POINT), a(0), b(0) {}
    float area() const override { return 0.0; }
    float getX() const { return a; }
    float getY() const { return b; }
};

class Circle : public Geometry {
    Point center;
    float radius;
public:
    Circle(float x, float y, float r) : Geometry(CIRCLE), center(x, y), radius(r) {}
    float area() const override { return PI * radius * radius; }
};

class Rectangle : public Geometry {
    Point p1, p2;
public:
    Rectangle(float x1, float y1, float x2, float y2) : Geometry(RECTANGLE), p1(x1, y1), p2(x2, y2) {}
    float area() const override {
        return abs(p2.getX() - p1.getX()) * abs(p2.getY() - p1.getY());
    }
};

class Square : public Geometry {
    Point p;
    float side;
public:
    Square(float x, float y, float s) : Geometry(SQUARE), p(x, y), side(s) {}
    float area() const override { return side * side; }
};

int main() {
    priority_queue<pair<float, int>> geoms;

    string shape;
    int index = 0;
    while (cin >> shape) {
        if (shape == "x"){
            break;
        }
        if (shape == "R") {
            float x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Rectangle r(x1, y1, x2, y2);
            geoms.push({r.area(), index});
        } else if (shape == "C") {
            float x, y, r;
            cin >> x >> y >> r;
            Circle c(x, y, r);
            geoms.push({c.area(), index});
        } else if (shape == "S") {
            float x, y, side;
            cin >> x >> y >> side;
            Square sq(x, y, side);
            geoms.push({sq.area(), index});
}
        index++;
    }

    while (!geoms.empty()) {
        cout << geoms.top().second << endl;
        geoms.pop();
    }

    return 0;
}
