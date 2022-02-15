#include "ReportGenerator.hpp"

int main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "Program must be launched with 2 arguments" << std::endl;
		std::cerr << "Example: ./<binary name> tests.json values.json" << std::endl;
		return 1;
	}
	ReportGenerator reporter;
	try {
		reporter.write_report_file(av[1], av[2]);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 2;
	}
	return 0;
}
