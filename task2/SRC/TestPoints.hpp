#pragma  once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <stdexcept>

using std::string;
using std::vector;
using pointsmap = std::unordered_multimap<float, float>;

struct Circle {
	float x, y, r2;
	Circle();
	Circle(float _x, float _y, float _r);
};

struct Parser {
	std::ifstream	scircle;
	std::ifstream	spoints;
	Parser();
	Parser(const char *circle_file, const char *points_file);
	~Parser();

	void open_files(const char *circle_file, const char *points_file);

	template <typename Delim>
	string get_word(std::istream& ss, Delim d) {
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

	vector<string> split(const string& s, const string& delim);
	pointsmap get_points();
	Circle get_circle();
};

struct Checker {
	bool rough_equal(float a, float b);
	int test_coordinates
	(const std::pair<float, float>& point, const Circle& circle);
};
