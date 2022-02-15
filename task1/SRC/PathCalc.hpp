#pragma  once
#include <vector>
#include <limits>
#include <iostream>
#include <stdexcept>

class PathCalc {
private:
	std::vector<int>	paths;
	int			elem_count;
	int			step;
	bool		 validate_input(const char* str);
	std::vector<int> accumulate_paths(int current);

public:
	PathCalc();
	PathCalc(const char *fst, const char *snd);
	PathCalc(const PathCalc& other) = default;
	PathCalc& operator = (const PathCalc& other) = default;
	~PathCalc() = default;

	void calculate_paths();
};
