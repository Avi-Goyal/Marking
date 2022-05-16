#include "Student.h"

const std::smatch validateIdentifier(std::string identifier) {
	std::regex regular_expression("^([A-Z]{2})([0-9]{8})$");
	std::smatch match;
	if (!std::regex_search(identifier, match, regular_expression)) {} //log
	return match;
}

const std::smatch validateEmail(std::string email) {
	// Regex magic because emails have a ton of edge cases.
	// https://stackoverflow.com/questions/201323/how-can-i-validate-an-email-address-using-a-regular-expression
	std::regex regular_expression(R"((?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9]))\.){3}(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9])|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\]))");
	std::smatch match;

	if (!std::regex_search(email, match, regular_expression)) {} //log

	return match;
}

// Constructor
Student::Student(const std::string& identifier, const std::string& given_name, const std::string& family_name, const std::string& email, const std::map<std::string, std::vector<double>>& grades, const std::map<std::string, CourseResult>& results) : given_name(given_name), family_name(family_name), grades(grades), results(results) {

	if (validateIdentifier(identifier).size() == 0) {
		throw std::runtime_error("Identifier " + identifier + " is invalid."); // Log error.
	}

	if (validateEmail(email).size() == 0) {
		throw std::runtime_error("Email " + email + " is invalid."); // Log error.
	}

};

const std::string Student::getIdentifier() const {
	return identifier;
}

const std::string Student::getGivenName() const {
	return given_name;
}

const std::string Student::getFamilyName() const {
	return family_name;
}

const std::string Student::getEmail() const {
	return email;
}

// This should take in a string and return the result, not the entire map. Ask James.
const std::map<std::string, std::vector<double>> Student::getGrades() const {
	return grades;
}

void Student::populateResults(CourseHolder courses) {

	std::vector<double> these_grades;

	for (auto const& map : courses.getCourseMap()) {

		getCourseGrades(map.first, &these_grades);
		results.insert({ map.first, (*map.second).getGrade(these_grades) });
	}
}

const std::map<std::string, CourseResult> Student::getResults() const {
	return results;
}

const bool Student::getCourseGrades(const std::string& courseCode, std::vector<double>* course_grades) const {

	if (getGrades().count(courseCode)) {

		*course_grades = getGrades().at(courseCode);
		return true;
	}
	else {

		//std::cout << getGivenName() + " " + getFamilyName() + " does not take " + courseCode + "." + '\n'; // Log
		return false;
	}
}