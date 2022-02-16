#include "TestPoints.hpp"

int main(int ac, char **av) {
	if (ac != 3) {
		std::cerr <<
			"Program must be launched with 2 arguments (text files)"
			<< std::endl;
		return 1;
	}
	Parser		parser;
	Circle		circle;
	pointsmap	points;
	try {
		parser.open_files(av[1], av[2]);
		circle = parser.get_circle();
		points = parser.get_points();
	} catch (std::exception& e) {
		std::cerr << "Parsing error:" << std::endl;
		std::cerr << e.what() << std::endl;
		return 2;
	}
	Checker checker;
	for (const auto& point: points)
		std::cout << checker.test_coordinates(point, circle) << std::endl;
	return 0;
}
