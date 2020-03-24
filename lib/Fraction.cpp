//
// Created by convi on 2020/3/23.
//

#include <iostream>
#include "Fraction.h"

Fraction::Fraction(int _up, int _down) {
    if (_up < 0 || _down <= 0) {
        std::cerr << "Error! Can not be zero or negative" << std::endl;
        exit(-1);
    }
    if (_up == 0) {
        this->up = _up;
        this->down = 1;
    } else {
        int d = gcd(abs(_up), abs(_down));
        this->up = _up / d;
        this->down = _down / d;
    }
}

Fraction::Fraction(int _up) {
    if (_up < 0) {
        std::cerr << "Error! Up can not be negative" << std::endl;
        exit(-1);
    }
    this->up = _up;
    this->down = 1;
}

Fraction::Fraction() : up(0), down(1) {}

Fraction Fraction::reduction(Fraction result) {
    if (result.down < 0) {
        result.up = -result.up;
        result.down = -result.down;
    }
    if (result.up == 0) {
        result.down = 1;
    } else {
        int d = gcd(abs(result.up), abs(result.down));
        result.up /= d;
        result.down /= d;
    }
    return result;
}

int Fraction::gcd(int a, int b) {
    int x = a > b ? a : b;
    int y = a < b ? a : b;
    int tmp;

    while (y) {
        tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}

int Fraction::ceil() {     //假设 this->up >= 0, this->down > 0
    if (this->up <= 0 || this->down <= 0)
        return 0;
    if (this->up < this->down)
        return 1;
    return this->up / this->down + 1;
}

int Fraction::floor() {    //假设 this->up > 0, this->down > 0
    if (this->up <= 0 || this->down <= 0)
        return -1;
    if (this->up <= this->down)
        return 0;
    if (this->up % this->down == 0)
        return this->up / this->down - 1;
    return this->up / this->down;
}

int Fraction::value() {
    if (this->up < 0 || this->down <= 0) {
        std::cerr << "Error! Negative value!" << std::endl;
        exit(-1);
    }
    Fraction f(this->up, this->down);
    f = reduction(f);
    if (f.down != 1) {
        std::cerr << "Error! No int value!" << std::endl;
        exit(-1);
    }
    return f.up;
}

bool Fraction::has_value() {
    if (this->up < 0 || this->down <= 0)
        return false;
    Fraction f(this->up, this->down);
    f = reduction(f);
    return f.down == 1;
}

Fraction Fraction::operator+(const Fraction &f) {
    Fraction res;
    res.up = this->up * f.down + f.up * this->down;
    res.down = this->down * f.down;
    return reduction(res);
}

Fraction Fraction::operator-(const Fraction &f) {
    Fraction res{};
    res.up = this->up * f.down - this->down * f.up;
    res.down = this->down * f.down;
    return reduction(res);
}

Fraction Fraction::operator*(const Fraction &f) {
    Fraction res{};
    res.up = this->up * f.up;
    res.down = this->down * f.down;
    return reduction(res);
}

Fraction Fraction::operator/(const Fraction &f) {
    Fraction res{};
    res.up = this->up * f.down;
    res.down = this->down * f.up;
    return reduction(res);
}

Fraction &Fraction::operator=(const Fraction &f) {
    if (this != &f) {
        this->up = f.up;
        this->down = f.down;
    }
    return *this;
}

Fraction Fraction::operator+=(const Fraction &f) {
    *this = *this + f;
    return *this;
}

Fraction Fraction::operator-=(const Fraction &f) {
    *this = *this - f;
    return *this;
}

Fraction Fraction::operator*=(const Fraction &f) {
    *this = *this * f;
    return *this;
}

Fraction Fraction::operator/=(const Fraction &f) {
    *this = *this / f;
    return *this;
}

bool Fraction::operator==(const Fraction &f) {
    Fraction res = reduction(f);
    return this->up == res.up && this->down == res.down;
}

bool Fraction::operator!=(const Fraction &f) {
    return !(*this == f);
}

Fraction Fraction::operator+(const int &i) {
    return (*this + Fraction(i));
}

Fraction Fraction::operator-(const int &i) {
    return (*this - Fraction(i));
}

Fraction Fraction::operator*(const int &i) {
    return (*this * Fraction(i));
}

Fraction Fraction::operator/(const int &i) {
    return (*this / Fraction(i));
}

Fraction Fraction::operator+=(const int &i) {
    *this = *this + i;
    return *this;
}

Fraction Fraction::operator-=(const int &i) {
    *this = *this - i;
    return *this;
}

Fraction Fraction::operator*=(const int &i) {
    *this = *this * i;
    return *this;
}

Fraction Fraction::operator/=(const int &i) {
    *this = *this / i;
    return *this;
}

Fraction &Fraction::operator=(const int &i) {
    this->up = i;
    this->down = 1;
    return *this;
}

bool Fraction::operator==(const int &i) {
    return (*this == Fraction(i));
}

bool Fraction::operator!=(const int &i) {
    return !(*this == i);
}

bool Fraction::operator>(const Fraction &f) {
    return (*this - f).up > 0;
}

bool Fraction::operator<(const Fraction &f) {
    return (*this - f).up < 0;
}

bool Fraction::operator>=(const Fraction &f) {
    return !(*this < f);
}

bool Fraction::operator<=(const Fraction &f) {
    return !(*this > f);
}

bool Fraction::operator>(const int &i) {
    return (*this > Fraction(i));
}

bool Fraction::operator<(const int &i) {
    return (*this < Fraction(i));
}

bool Fraction::operator>=(const int &i) {
    return !(*this < i);
}

bool Fraction::operator<=(const int &i) {
    return !(*this > i);
}


