#include "TestPoints.hpp"

Circle::Circle(): x(0), y(0), r2(0) {}
Circle::Circle(float _x, float _y, float _r): x(_x), y(_y), r2(powf(_r, 2)) {}
