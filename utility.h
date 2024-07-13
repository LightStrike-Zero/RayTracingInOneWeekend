//
// Created by Shaun on 9/07/2024.
//

#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>


// C++ Std Usings

using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Function to generate a random double between 0 and 1 using <random>
inline double random_double() {
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 generator(rd()); // Seed the generator
    static std::uniform_real_distribution<double> distribution(0.0, 1.0); // Define the range
    return distribution(generator);
}

// Function to generate a random double between min and max using <random>
inline double random_double(double min, double max) {
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 generator(rd()); // Seed the generator
    std::uniform_real_distribution<double> distribution(min, max); // Define the range
    return distribution(generator);
}

// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif
