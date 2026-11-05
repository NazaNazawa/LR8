#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <windows.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Triad {
protected:
    double first;
    double second;
    double third;

public:
    Triad() : first(0.0), second(0.0), third(0.0) {}
    Triad(double f, double s, double t) : first(f), second(s), third(t) {}
    virtual ~Triad() = default;

    virtual void setFields(double f, double s, double t) {
        first = f;
        second = s;
        third = t;
    }

    void setFirst(double f) { first = f; }
    void setSecond(double s) { second = s; }
    void setThird(double t) { third = t; }

    double getFirst() const { return first; }
    double getSecond() const { return second; }
    double getThird() const { return third; }

    virtual double sum() const {
        return first + second + third;
    }

    virtual void print() const {
        std::cout << "Triad(" << first << ", " << second << ", " << third << ")";
    }
};

class Triangle : public Triad {
public:
    Triangle() : Triad(3.0, 4.0, 5.0) {
        validateSides();
    }

    Triangle(double a, double b, double c) : Triad(a, b, c) {
        validateSides();
    }

    void setFields(double a, double b, double c) override {
        first = a;
        second = b;
        third = c;
        validateSides();
    }

    void validateSides() const {
        if (first <= 0 || second <= 0 || third <= 0) {
            throw std::invalid_argument("Sides must be positive");
        }
        if (first + second <= third || first + third <= second || second + third <= first) {
            throw std::invalid_argument("Invalid triangle sides");
        }
    }

    double perimeter() const {
        return sum();
    }

    double area() const {
        double p = perimeter() / 2.0;
        return std::sqrt(p * (p - first) * (p - second) * (p - third));
    }

    void calculateAngles(double& angleA, double& angleB, double& angleC) const {
        double cosA = (second * second + third * third - first * first) / (2.0 * second * third);
        double cosB = (first * first + third * third - second * second) / (2.0 * first * third);
        double cosC = (first * first + second * second - third * third) / (2.0 * first * second);

        cosA = (std::max)(-1.0, (std::min)(1.0, cosA));
        cosB = (std::max)(-1.0, (std::min)(1.0, cosB));
        cosC = (std::max)(-1.0, (std::min)(1.0, cosC));

        angleA = std::acos(cosA) * 180.0 / M_PI;
        angleB = std::acos(cosB) * 180.0 / M_PI;
        angleC = std::acos(cosC) * 180.0 / M_PI;
    }

    void print() const override {
        std::cout << "Triangle(" << first << ", " << second << ", " << third << ")";
    }
};

Triad processTriad(const Triad& t) {
    t.print();
    std::cout << " sum=" << t.sum() << "\n";
    return Triad(t.getFirst() * 2, t.getSecond() * 2, t.getThird() * 2);
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Triad t1(1.5, 2.5, 3.0);
    t1.print();
    std::cout << " sum=" << t1.sum() << "\n";

    Triangle tr1(3.0, 4.0, 5.0);
    tr1.print();
    std::cout << " P=" << tr1.perimeter() << " S=" << tr1.area() << "\n";

    double a, b, c;
    tr1.calculateAngles(a, b, c);
    std::cout << "Angles: " << a << ", " << b << ", " << c << "\n";

    try {
        Triangle tr_invalid(1.0, 2.0, 10.0);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    Triangle myTriangle(6.0, 8.0, 10.0);
    Triad res = processTriad(myTriangle);
    res.print();
    std::cout << "\n";

    Triad* pTriad = new Triangle(5.0, 12.0, 13.0);
    pTriad->print();
    std::cout << " sum=" << pTriad->sum() << "\n";
    delete pTriad;

    return 0;
}