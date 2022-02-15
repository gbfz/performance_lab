#include "PathCalc.hpp"

int main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "Program must be launched with 2 integer arguments" << std::endl;
		std::cerr << "Example: ./<binary name> 5 4" << std::endl;
		return 1;
	}
	PathCalc calc;
	try {
		calc = PathCalc(av[1], av[2]);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	calc.calculate_paths();
	return 0;
}
