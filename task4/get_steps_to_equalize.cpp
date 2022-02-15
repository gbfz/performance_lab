#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int get_steps_to_equalize(std::vector<int>& data) {
	std::sort(data.begin(), data.end());
	int median = data[data.size() / 2];
	int steps = 0;
	for (int i: data)
		steps += std::abs(median - i);
	return steps;
}

std::vector<int> get_data(std::istream& input) {
	std::string line;
	std::vector<int> data;
	while (std::getline(input, line))
		data.push_back(std::stoi(line));
	return data;
}

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr <<
			"Program must be launched with 1 argument (text file)"
			<< std::endl;
		return 1;
	}
	std::ifstream input(av[1]);
	if (!input.is_open()) {
		std::cerr << "Couldn't open file to read" << std::endl;
		return 2;
	}
	std::vector<int> data;
	try {
		data = get_data(input);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		input.close();
		return 3;
	}
	std::cout << get_steps_to_equalize(data) << std::endl;
	input.close();
	return 0;
}
