#include "TestPoints.hpp"

Parser::Parser() {}

Parser::Parser(const char *circle_file, const char *points_file) {
	scircle.open(circle_file);
	if (!scircle.is_open()) {
		throw std::invalid_argument(
			"Couldn't open circle file"
		);
	}
	spoints.open(points_file);
	if (!spoints.is_open()) {
		scircle.close();
		throw std::invalid_argument(
			"Couldn't open points file"
		);
	}
}

Parser::~Parser() {
	scircle.close();
	spoints.close();
}

void Parser::open_files(const char *circle_file, const char *points_file) {
	scircle.open(circle_file);
	if (!scircle.is_open()) {
		throw std::invalid_argument(
			"Couldn't open circle file"
		);
	}
	spoints.open(points_file);
	if (!spoints.is_open()) {
		scircle.close();
		throw std::invalid_argument(
			"Couldn't open points file"
		);
	}
}

vector<string> Parser::split(const string& s, const string& delim) {
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

pointsmap Parser::get_points() {
	pointsmap	data;
	vector<string>	words;
	string		line;

	while (std::getline(spoints, line)) {
		words = split(line, " \t");
		if (words.size() != 2)
			throw std::invalid_argument(
				"Garbage value in points file"
			);
		try {
			data.insert(std::make_pair
					(std::stof(words[0]), std::stof(words[1]))
			);
		} catch (...) {
			throw std::invalid_argument(
				"Garbage value in points file"
			);
		}
	}
	return data;
}

Circle Parser::get_circle() {
	Circle	c;
	string	line;

	std::getline(scircle, line);
	vector<string> words = split(line, " \t");
	if (words.size() != 2)
		throw std::invalid_argument(
			"Garbage value in circle file"
		);
	try {
		c.x = std::stof(words[0]);
		c.y = std::stof(words[1]);
		std::getline(scircle, line);
		c.r2 = powf(std::stof(line), 2);
	} catch (...) {
		throw std::invalid_argument(
			"Garbage value in circle file"
		);
	}
	if (std::getline(scircle, line)) {
		throw std::invalid_argument(
			"Circle file does not match required format"
		);
	}
	return c;
}
