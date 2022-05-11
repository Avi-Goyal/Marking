#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <map>
#include <regex>
#include <fstream>
#include <nlohmann/json.hpp>
#include "CourseResult.h"

class Student {

	std::string identifier{}, givenName{}, familyName{}, email{};
	std::map<std::string, std::vector<double>> grades{};
	std::map<std::string, CourseResult> results{};

	Student(std::string identifier, std::string givenName, std::string familyName, std::string email, std::map<std::string, std::vector<double>> grades, std::map<std::string, CourseResult> results);
	explicit Student(const std::string& file_path_name);

	std::string getIdentifier();
	std::string getGivenName();
	std::string getFamilyName();
	std::string getEmail();
	std::map<std::string, std::vector<double>> getGrades();
	std::map<std::string, CourseResult> getResults();

	std::smatch validateIdentifier(const std::string& identifier);
	std::smatch validateEmail(const std::string& email);

};