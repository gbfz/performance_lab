#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <stdexcept>

using namespace std;

struct Circle {
	float x;
	float y;
	float r;
	float r2;
	Circle(float _x, float _y, float _r): x(_x), y(_y), r(_r), r2(powf(r, 2)) {}
	Circle(): x(0), y(0), r(0), r2(0) {}
};

bool rough_equal(float a, float b) {
	return std::abs(a - b) < std::numeric_limits<float>::epsilon();
}

int test_coordinates(float px, float py, const Circle& c) {
	float sum = powf(px - c.x, 2) + powf(py - c.y, 2);
	if (rough_equal(sum, c.r2))
		return 0;
	if (sum < c.r2)
		return 1;
	return 2;
}

template <typename Delim>
std::string get_word(std::istream& ss, Delim d) {
	string word;
	for (char ch; ss.get(ch); ) {
		if (!d(ch)) {
			word.push_back(ch);
			break;
		}
	}
	for (char ch; ss.get(ch); ) {
		if (!d(ch))
			word.push_back(ch);
		else return word;
	}
	return word;
}

std::vector<std::string> split(const std::string& s, const std::string& delim) {
	std::stringstream ss(s);
	auto del = [&](char ch) -> bool {
		for (auto x : delim)
			if (x == ch) return true;
		return false;
	};
	std::vector<std::string> words;
	for (std::string w; (w = get_word(ss, del)) != ""; )
		words.push_back(w);
	return words;
}

std::unordered_multimap<float, float>	get_points(std::istream& input) {
	std::unordered_multimap<float, float> data;
	std::vector<std::string> words;
	std::string line;
	while (std::getline(input, line)) {
		words = split(line, " \t");
		if (words.size() != 2)
			throw std::invalid_argument("Garbage value in points file");
		data.insert(std::make_pair(std::stof(words[0]), std::stof(words[1])));
	}
	return data;
}

Circle	get_circle(std::istream& input) {
	Circle		c;
	std::string	line;

	std::getline(input, line);
	std::vector<std::string> words = split(line, " \t");
	if (words.size() != 2)
		throw std::invalid_argument("Garbage value in circle file");
	c.x = std::stof(words[0]);
	c.y = std::stof(words[1]);
	std::getline(input, line);
	c.r = std::stof(line);
	c.r2 = powf(c.r, 2);
	return c;
}

int main(int ac, char **av) {
	if (ac != 3) {
		std::cerr <<
			"Program must be launched with 2 arguments (text file)"
			<< std::endl;
		return 1;
	}
	std::ifstream scircle(av[1]);
	if (!scircle.is_open()) {
		std::cerr << "Couldn't open file with circle info" << std::endl;
		return 2;
	}
	std::ifstream spoints(av[2]);
	if (!spoints.is_open()) {
		std::cerr << "Couldn't open file with points info" << std::endl;
		scircle.close();
		return 2;
	}
	try {
		auto data = get_points(spoints);
		auto circle = get_circle(scircle);
		for (const auto& p: data)
			cout << test_coordinates(p.first, p.second, circle) << endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		scircle.close();
		spoints.close();
		return 3;
	}
	scircle.close();
	spoints.close();
	return 0;
}
