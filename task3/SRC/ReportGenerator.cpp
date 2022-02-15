#include "ReportGenerator.hpp"

// Carefully opens files to read/write
void 	ReportGenerator::open_files
(const char *tests_filename, const char *value_filename) {
	tests_file = std::ifstream(tests_filename);
	if (!tests_file.is_open())
		throw std::invalid_argument("Couldn't open tests file");
	value_file = std::ifstream(value_filename);
	if (!value_file.is_open()) {
		tests_file.close();
		throw std::invalid_argument("Couldn't open values file");
	}
	report_file = std::ofstream("report.json", std::ios::out | std::ios::trunc);
	if (!report_file.is_open()) {
		tests_file.close();
		value_file.close();
		throw std::invalid_argument("Couldn't open report file for writing");
	}
}

// Constructor that takes filenames
ReportGenerator::ReportGenerator
(const char *tests_filename, const char *value_filename) {
	open_files(tests_filename, value_filename);
}

ReportGenerator::~ReportGenerator() {
	tests_file.close();
	value_file.close();
	report_file.close();
}

// Generate report.json based on files previously opened by object
void	ReportGenerator::write_report_file() {
	json_parser::read_json(tests_file, tests_tree);
	json_parser::read_json(value_file, value_tree);

	value_tree = value_tree.get_child("values");
	const ptree& json_data = get_report_array(tests_tree.get_child("tests"));
	report_tree.push_back(ptree::value_type("tests", json_data));

	json_parser::write_json(report_file, report_tree);
}

// Generate report.json based on filenames passed to method 
void	ReportGenerator::write_report_file
(const char *tests_filename, const char *value_filename) {
	if (tests_file.is_open() && value_file.is_open())
		return write_report_file();
	open_files(tests_filename, value_filename);
	write_report_file();
}

// Generate data as JSON array to maintain example structure
ptree	ReportGenerator::get_report_array(const ptree& test_entry) {
	ptree	report_array;
	for (const auto& object: test_entry) {
		report_array.push_back(
			ptree::value_type("", get_report_entry(object.second))
		);
	}
	return report_array;
}

// Generate single report entry
ptree	ReportGenerator::get_report_entry(const ptree& test_entry) {
	ptree report_entry = write_report_entry(test_entry);
	const auto& child = test_entry.get_child_optional("values");
	if (child) {
		report_entry.push_back(
			ptree::value_type("values", get_report_array(*child))
		);
	}
	return report_entry;
}

// Write data to single report entry
ptree	ReportGenerator::write_report_entry(const ptree& test_entry) {
	ptree report_entry;
	const std::string& test_id = test_entry.get<std::string>("id");
	report_entry.put("id", test_id);
	report_entry.put("title", test_entry.get<std::string>("title"));
	if (test_entry.get_child_optional("value"))
		report_entry.put("value", get_test_result(test_id));
	return report_entry;
}

// Hepler method to get possibly missing data or ""
std::string	ReportGenerator::get_test_result(const std::string& id) {
	for (const auto& object: value_tree) {
		auto entry = object.second;
		if (entry.get<std::string>("id") == id)
			return entry.get<std::string>("value");
	}
	throw std::invalid_argument("Couldn't find requested data in values file");
}
