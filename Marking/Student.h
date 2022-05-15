#pragma once
#include <string>
#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include <regex>
#include <iostream>
#include <fstream>
#include "CourseResult.h"
#include "CourseHolder.h"


using json = nlohmann::json;

class Student {

public:

	// variables:
	std::string identifier{}, given_name{}, family_name{}, email{};
	std::map<std::string, std::vector<double>> grades{};
	std::map<std::string, CourseResult> results{};

	// default constructor
	Student() = default;

	// Constructors.
	Student(std::string identifier, std::string given_name, std::string family_name, std::string email, std::map<std::string, std::vector<double>> grades, std::map<std::string, CourseResult> results);
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, identifier, given_name, family_name, email, grades);

	// Methods.
	std::string getIdentifier();
	std::string getGivenName();
	std::string getFamilyName();
	std::string getEmail();
	std::map<std::string, std::vector<double>> getGrades();
	void populateResults(CourseHolder courses);
    std::map<std::string, CourseResult> getResults();
	
	//std::smatch validateIdentifier();
	//std::smatch validateEmail();

	bool getCourseGrades(std::string courseCode, std::vector<double>* course_grades);

	
};
