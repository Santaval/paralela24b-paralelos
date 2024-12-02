// Copyright Aaron Jose Santana Valdelomar - Universidad de Costa Rica 2024

#include "Vector.hpp"

Vector::Vector(magnitude_t x, magnitude_t y, magnitude_t z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector::~Vector() {}

void Vector::operator*(magnitude_t scalar) {
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
}

Vector Vector::operator+(const Vector& other) {
    return Vector(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector Vector::operator-(const Vector& other) {
    return Vector(this->x - other.x, this->y - other.y, this->z - other.z);
}

