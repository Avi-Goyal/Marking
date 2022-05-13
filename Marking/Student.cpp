#include "Student.h"

using json = nlohmann::json;

std::smatch validateIdentifier(std::string identifier) {
	std::regex regular_expression("^([A-Z]{2})([0-9]{8})$");
	std::smatch match;
	if (!std::regex_search(identifier, match, regular_expression)) {} //log
	return match;
}

std::smatch validateEmail(std::string email) {
	std::regex regular_expression("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	std::smatch match;
	if (!std::regex_search(email, match, regular_expression)) {} //log
	return match;
}

// Constructor
Student::Student(std::string tmp_identifier, std::string givenName, std::string familyName, std::string tmp_email, std::map<std::string, std::vector<double>> grades, std::map<std::string, CourseResult> results) : givenName(givenName), familyName(familyName), grades(grades), results(results) {

	if (validateIdentifier(tmp_identifier).size() != 0) {
		identifier = tmp_identifier;
	} else {
		throw std::runtime_error("Identifier " + tmp_identifier + " is invalid."); // Log error.
	}

	if (validateEmail(tmp_email).size() != 0) {
		email = tmp_email;
	} else {
		throw std::runtime_error("Email " + tmp_email + " is invalid."); // Log error.
	}

};

std::string Student::getIdentifier() {
	return identifier;
}

std::string Student::getGivenName() {
	return givenName;
}

std::string Student::getFamilyName() {
	return familyName;
}

std::string Student::getEmail() {
	return email;
}

// This should take in a string and return the result, not the entire map. Ask James.
std::map<std::string, std::vector<double>> Student::getGrades() {
	return grades;
}

void Student::populateResults(CourseHolder courses) {

	std::vector<double> these_grades;

	for (auto const& map : courses.getCourseMap()) {

		getCourseGrades(map.first, &these_grades);
		results.insert({ map.first, (*map.second).getGrade(these_grades) });
	}
}

std::map<std::string, CourseResult> Student::getResults() {
	return results;
}

bool Student::getCourseGrades(std::string courseCode, std::vector<double>* course_grades) {

	if (getGrades().count(courseCode)) {

		*course_grades = getGrades().at(courseCode);
		return true;
	}
	else {

		std::cout << getGivenName() + " " + getFamilyName() + " does not take " + courseCode + "." + '\n';
		return false;
	}
}