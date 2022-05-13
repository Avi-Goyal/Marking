#include "Student.h"

using json = nlohmann::json;

// Ask James about std::smatch being returned and for automated testing.
// Do use smatch because regex_search always returns true if that works. Same as the passing by pointer functions. - James
bool validateIdentifier(std::string identifier) {
	std::regex regular_expression("^([A-Z]{2})([0-9]{8})$");
	std::smatch match;
	// TODO: Log info
	return std::regex_search(identifier, match, regular_expression);
}

bool validateEmail(std::string email) {
	std::regex regular_expression("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	std::smatch match;
	// TODO: Log info
	return std::regex_search(email, match, regular_expression);
}

// Constructor
Student::Student(std::string tmp_identifier, std::string givenName, std::string familyName, std::string tmp_email, std::map<std::string, std::vector<double>> grades, std::map<std::string, CourseResult> results) : givenName(givenName), familyName(familyName), email(email), grades(grades), results(results) {

	if (validateIdentifier(tmp_identifier)) {
		identifier = tmp_identifier;
	} else {
		throw std::runtime_error("Identifier " + tmp_identifier + " is invalid."); // Log error.
	}

	if (validateEmail(tmp_email)) {
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

std::map<std::string, CourseResult> Student::getResults() {
	return results = results;
}
