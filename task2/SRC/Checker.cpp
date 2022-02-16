#include "TestPoints.hpp"

bool Checker::rough_equal(float a, float b) {
	return std::abs(a - b) < std::numeric_limits<float>::epsilon();
}

int Checker::test_coordinates
(const std::pair<float, float>& point, const Circle& circle) {
	float sum = powf(point.first - circle.x, 2) +
		    powf(point.second - circle.y, 2);
	if (rough_equal(sum, circle.r2))
		return 0;
	if (sum < circle.r2)
		return 1;
	return 2;
}
