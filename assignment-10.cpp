#include <queue>
#include <vector>
#include <iostream>
#include <cmath>
#define PI 3.14

using namespace std;

class Geometry {
public:
    int index;
    virtual float area() const = 0;
    virtual ~Geometry() {}
};

class Point: public Geometry {
    float a, b;
public:
    Point(float x, float y) : a(x), b(y) {}
    Point() {}
    float area() const { return 0.0; }
    float getX() const { return a; }
    float getY() const { return b; }
};

class Circle: public Geometry {
    Point center;
    float radius;
public:
    Circle(float x, float y, float r) : center(x, y), radius(r) {}
    float area() const { return PI * radius * radius; }
};

class Rectangle: public Geometry {
    Point p1;
    Point p2;
public:
    Rectangle(float x1, float y1, float x2, float y2) : p1(x1, y1), p2(x2, y2) {}
    float area() const { return std::abs(p2.getX() - p1.getX()) * std::abs(p2.getY() - p1.getY()); }
};

class Square: public Geometry {
    Point p;
    float side;
public:
    Square(float x, float y, float s) : p(x, y), side(s) {}
    float area() const { return side * side; }
};

void bubbleSort(vector<Geometry*>& vec) {
    bool swapped;
    int n = vec.size();
    do {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (vec[i - 1]->area() < vec[i]->area()) {
                swap(vec[i - 1], vec[i]);
                swapped = true;
            }
        }
        --n;
    } while (swapped);
}

int main() {
    priority_queue<Geometry*> geoms;
    vector<Geometry*> geomVector;
    vector<int> indices;
    string type;
    int index = 0;

    while (cin >> type) {
        Geometry* geom = nullptr;
        if (type == "R") {
            float x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            geom = new Rectangle(x1, y1, x2, y2);
        } else if (type == "S") {
            float x, y, s;
            cin >> x >> y >> s;
            geom = new Square(x, y, s);
        } else if (type == "C") {
            float x, y, r;
            cin >> x >> y >> r;
            geom = new Circle(x, y, r);
        }
        if (geom != nullptr) {
            geom->index = index++;
            geoms.push(geom);
        }
    }

    while (!geoms.empty()) {
        geomVector.push_back(geoms.top());
        geoms.pop();
    }

    bubbleSort(geomVector);

    for (auto i = geomVector.begin(); i != geomVector.end(); i++) {
        indices.push_back((*i)->index);
    }

    for (auto i = indices.begin(); i != indices.end(); i++) {
        cout << *i << endl;
    }

    for (auto i = geomVector.begin(); i != geomVector.end(); i++) {
        delete *i;
    }

    return 0;
}
