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

const class Student {
 private:
	// Variables:
	std::string identifier{}, given_name{}, family_name{}, email{};
	std::map<std::string, std::vector<double>> grades{};
	std::map<std::string, CourseResult> results{};
 public:

	// Constructors.
	Student(const std::string& identifier, const std::string& given_name, const std::string& family_name, const std::string& email, const std::map<std::string, std::vector<double>>& grades, const std::map<std::string, CourseResult>& results);
	Student() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, identifier, given_name, family_name, email, grades);

	// Methods.
	const std::string getIdentifier() const;
	const std::string getGivenName() const;
	const std::string getFamilyName() const;
	const std::string getEmail() const;
	const std::map<std::string, std::vector<double>> getGrades() const;
	void populateResults(CourseHolder courses);
	const std::map<std::string, CourseResult> getResults() const;
	bool getCourseGrades(std::string courseCode, std::vector<double>* course_grades);

};
