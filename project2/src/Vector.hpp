// Copyright Aaron Santana Valdelomar - Univerdidad de Costa Rica 2024
#pragma once
#include "defines.hpp"
class Vector {
 private:
    /**
     * @brief Represents the x, y, and z components of a vector.
     * 
     * @var x The x component of the vector.
     * @var y The y component of the vector.
     * @var z The z component of the vector.
     */
    magnitude_t x, y, z;
 public:
    /**
     * @brief Constructs a Vector with the given x, y, and z components.
     * 
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     * @param z The z component of the vector.
     */
    Vector(magnitude_t x, magnitude_t y, magnitude_t z);
    /**
     * @brief Destructor for the Vector class.
     * 
     * This destructor is responsible for cleaning up any resources
     * allocated by the Vector class. It ensures that memory is properly
     * deallocated and any other necessary cleanup tasks are performed.
     */
    ~Vector();
    /**
     * @brief Multiplies the vector by a scalar value.
     * 
     * This operator overload allows for the multiplication of the vector
     * by a scalar value, effectively scaling the vector by the given magnitude.
     * 
     * @param scalar The scalar value to multiply the vector by.
     */
    void operator*(magnitude_t scalar);
    /**
     * @brief Overloads the + operator to add two Vector objects.
     * 
     * @param other The Vector object to be added.
     * @return A new Vector object that is the result of the addition.
     */
    Vector operator+(const Vector& other);
    /**
     * @brief Overloads the subtraction operator to subtract two Vector objects.
     * 
     * @param other The Vector object to be subtracted from the current Vector.
     * @return Vector The result of the subtraction as a new Vector object.
     */
    Vector operator-(const Vector& other);
};
