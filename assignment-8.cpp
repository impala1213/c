#include <iostream>
#include <cmath>
#define PI  3.14

using namespace std;

class Geom {
protected:
    int type;
public:
    enum {RECT, CIRCLE, SQUARE, POINT};
    Geom(int t): type(t) {}
    Geom() {}
    virtual bool overlap(Geom* other) = 0;
    virtual void print(ostream& out) const = 0;
    friend ostream& operator<<(ostream& out, const Geom& geom) {
        geom.print(out);
        return out;
    }
    int getType() const { return type; }
};

class Point {
    float a, b;
public:
    Point(float x, float y): a(x), b(y) {}
    Point() : a(0), b(0) {}
    float getA() const { return a; }
    float getB() const { return b; }
};

class Circle: public Geom {
    Point center;
    float radius;
public:
    Circle(float x, float y, float r):
        Geom(CIRCLE), center(x, y), radius(r) {}
    Circle() {}
    bool overlap(Geom* other);
    float getCenterX() const { return center.getA(); }
    float getCenterY() const { return center.getB(); }
    float getRadius() const { return radius; }
    void print(ostream& out) const {
        out << "Circle: (" << getCenterX() << ", " << getCenterY() << "), r=" << getRadius();
    }
};

class Rectangle: public Geom {
    Point p1;
    Point p2;
public:
    Rectangle(float x1, float y1, float x2, float y2):
        Geom(RECT), p1(x1, y1), p2(x2, y2) {}
    Rectangle() {}
    bool overlap(Geom* other);
    Point getP1() const { return p1; }
    Point getP2() const { return p2; }
    void print(ostream& out) const {
        out << "Rectangle: [(" << p1.getA() << ", " << p1.getB() << "), (" << p2.getA() << ", " << p2.getB() << ")]";
    }
};

class Square: public Geom {
    Point p;
    float side;
public:
    Square(float x, float y, float s): Geom(SQUARE), p(x, y), side(s) {}
    Square() {}
    bool overlap(Geom* other);
    Point getP() const { return p; }
    float getSide() const { return side; }
    void print(ostream& out) const {
        out << "Square: [(" << p.getA() << ", " << p.getB() << "), side=" << side << "]";
    }
};

bool rectOverlap(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    return !(x1 > x4 || x3 > x2 || y1 > y4 || y3 > y2);
}

bool Circle::overlap(Geom* other) {
    if (other->getType() == CIRCLE) {
        Circle* c = dynamic_cast<Circle*>(other);
        if (c == nullptr) return false;
        float dist = std::sqrt((center.getA() - c->center.getA()) * (center.getA() - c->center.getA()) +
                               (center.getB() - c->center.getB()) * (center.getB() - c->center.getB()));
        return dist <= (radius + c->radius);
    } else if (other->getType() == RECT || other->getType() == SQUARE) {
        Rectangle* r = dynamic_cast<Rectangle*>(other);
        if (r == nullptr) return false;
        float closestX = center.getA() < r->getP1().getA() ? r->getP1().getA() : (center.getA() > r->getP2().getA() ? r->getP2().getA() : center.getA());
        float closestY = center.getB() < r->getP1().getB() ? r->getP1().getB() : (center.getB() > r->getP2().getB() ? r->getP2().getB() : center.getB());
        float distX = center.getA() - closestX;
        float distY = center.getB() - closestY;
        return (distX * distX + distY * distY) <= (radius * radius);
    }
    return false;
}

bool Rectangle::overlap(Geom* other) {
    if (other->getType() == RECT) {
        Rectangle* r = dynamic_cast<Rectangle*>(other);
        if (r == nullptr) return false;
        return rectOverlap(p1.getA(), p1.getB(), p2.getA(), p2.getB(), r->getP1().getA(), r->getP1().getB(), r->getP2().getA(), r->getP2().getB());
    } else if (other->getType() == SQUARE) {
        Square* s = dynamic_cast<Square*>(other);
        if (s == nullptr) return false;
        return rectOverlap(p1.getA(), p1.getB(), p2.getA(), p2.getB(), s->getP().getA(), s->getP().getB(), s->getP().getA() + s->getSide(), s->getP().getB() + s->getSide());
    } else if (other->getType() == CIRCLE) {
        return other->overlap(this);
    }
    return false;
}

bool Square::overlap(Geom* other) {
    if (other->getType() == RECT || other->getType() == SQUARE) {
        Rectangle* r = dynamic_cast<Rectangle*>(other);
        if (r == nullptr) return false;
        return rectOverlap(p.getA(), p.getB(), p.getA() + side, p.getB() + side, r->getP1().getA(), r->getP1().getB(), r->getP2().getA(), r->getP2().getB());
    } else if (other->getType() == CIRCLE) {
        Circle* c = dynamic_cast<Circle*>(other);
        if (c == nullptr) return false;
        float closestX = c->getCenterX() < p.getA() ? p.getA() : (c->getCenterX() > p.getA() + side ? p.getA() + side : c->getCenterX());
        float closestY = c->getCenterY() < p.getB() ? p.getB() : (c->getCenterY() > p.getB() + side ? p.getB() + side : c->getCenterY());
        float distX = c->getCenterX() - closestX;
        float distY = c->getCenterY() - closestY;
        return (distX * distX + distY * distY) <= (c->getRadius() * c->getRadius());
    }
    return false;
}


int main() {
    int numGeom;
    cin >> numGeom;
    Geom* geoms[numGeom];

    for(int i = 0; i < numGeom; i++) {
        char type;
        cin >> type;
        if (type == 'R') {
            float x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            geoms[i] = new Rectangle(x1, y1, x2, y2);
        } else if (type == 'S') {
            float x, y, s;
            cin >> x >> y >> s;
            geoms[i] = new Square(x, y, s);
        } else if (type == 'C') {
            float x, y, r;
            cin >> x >> y >> r;
            geoms[i] = new Circle(x, y, r);
        }
    }

    char qType;
    cin >> qType;
    Geom* queryGeom;
    if (qType == 'R') {
        float x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        queryGeom = new Rectangle(x1, y1, x2, y2);
    } else if (qType == 'S') {
        float x, y, s;
        cin >> x >> y >> s;
        queryGeom = new Square(x, y, s);
    } else if (qType == 'C') {
        float x, y, r;
        cin >> x >> y >> r;
        queryGeom = new Circle(x, y, r);
    }

    int result = -1;
    for(int i = 0; i < numGeom; i++) {
        if(queryGeom->overlap(geoms[i])) {
            result = i + 1;
            break;
        }
    }

    cout << result << endl;

    delete queryGeom;
    for (int i=0; i < numGeom; i++){
        delete geoms[i];
    }
    return 0;
}
