#include "PathCalc.hpp"

PathCalc::PathCalc(): paths(std::vector<int>(1, 1)), elem_count(1), step(0) {}

PathCalc::PathCalc(const char* fst, const char* snd) {
	if (!validate_input(fst) || !validate_input(snd))
		throw std::invalid_argument \
			("Input must be an integer and greater than 1");
	this->paths = std::vector<int>(1, 1);
	this->elem_count = atoi(fst);
	this->step = atoi(snd) - 1 ?: 1;
}

bool
PathCalc::validate_input(const char* str) {
	auto input = std::strtoll(str, nullptr, 10);
	if (input <= 1)
		return false;
	if (input < std::numeric_limits<int>::min())
		return false;
	if (input > std::numeric_limits<int>::max())
		return false;
	return true;
}

std::vector<int>
PathCalc::accumulate_paths(int current) {
	current += step;
	if (current > elem_count)
		current %= elem_count;
	if (current <= 1)
		return paths;
	paths.push_back(current);
	return accumulate_paths(current);
}

void
PathCalc::calculate_paths() {
	for (int i: this->accumulate_paths(1))
		std::cout << i;
	std::cout << std::endl;
}
