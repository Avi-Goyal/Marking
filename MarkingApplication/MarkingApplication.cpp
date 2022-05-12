#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"
#include "..\Marking\Course.cpp"
#include "..\Marking\CourseResult.cpp"
#include "..\Marking\Student.cpp"
#include <iostream>
#include <cassert>
#include <vector>
#include <regex>
#include<string>
#include<map>
#include <cmath>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <nlohmann/json.hpp>
#include<cmath>

using json = nlohmann::json;

void print_vector(std::vector<double> const& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
}


void print_map(std::map<std::string, std::vector<double>> const& m)
{
	for (auto const& pair : m) {
		std::cout << "{" << pair.first << ": "; print_vector(pair.second); std::cout << "}" << std::endl;
	}
}


int main() {
   /* std::map<std::string, std::vector<double>> grades = { {"MATH1", {1,2,3,4} }, {"MATH2", {1,2,3,4} } };
    CourseResult test(60.0, true);
    std::map<std::string, CourseResult> results = { {"MATH1", CourseResult(60, true)}, {"MATH2", CourseResult(80, true)} };
    std::cout << std::boolalpha << test.getResult() << std::endl;
    std::cout << test.getScore() << std::endl;

    Student test_1("YY12345678", "Jack", "Smith", "Jack@gmail.com", grades, results);
    std::cout << test_1.getEmail() << std::endl;*/



	std::string amf = "AMF123", nla = "NLA123";
	std::vector<double> grades_amf = { 50, 40, 70 };
	std::vector<double> grades_nla = { 35, 80, 100 };
	std::map<std::string, std::vector<double>> grades;
	grades.insert({ amf, grades_amf }); grades.insert({ nla, grades_nla });
	std::map<std::string, CourseResult> results{};

	Student s("123", "John", "Smith", "js@gmail.com", grades, results);
	json j1 = s;
	std::cout << j1;















	system("pause>0");
	return 0;

}
