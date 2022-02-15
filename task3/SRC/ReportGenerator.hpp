#pragma  once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace boost::property_tree;

class ReportGenerator {
private:
	ptree	tests_tree;
	ptree	value_tree;
	ptree	report_tree;

	std::ifstream	tests_file;
	std::ifstream	value_file;
	std::ofstream	report_file;

	void	open_files(const char *tests_filename, const char * value_filename);
	ptree	get_report_array(const ptree& test_entry);
	ptree	get_report_entry(const ptree& test_entry);
	ptree	write_report_entry(const ptree& test_entry);
	std::string	get_test_result(const std::string& id);

	ReportGenerator(const ReportGenerator& other) = delete;
	ReportGenerator& operator = (const ReportGenerator& other) = delete;
public:
	ReportGenerator() = default;
	ReportGenerator(const char* tests_filename, const char *value_filename);
	~ReportGenerator();

	void	write_report_file();
	void	write_report_file(const char *tests_filename, const char *value_filename);
};
