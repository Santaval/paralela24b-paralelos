// Copyright Aaron Jose Santana Valdelomar - Universidad de Costa Rica 2024

#include "Vector.hpp"
#include <cmath>

Vector::Vector(magnitude_t x, magnitude_t y, magnitude_t z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::Vector() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector::~Vector() {}

Vector Vector::operator*(magnitude_t scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

Vector Vector::operator+(const Vector& other) {
    return Vector(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(this->x - other.x, this->y - other.y, this->z - other.z);
}

magnitude_t Vector::magnitude() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

