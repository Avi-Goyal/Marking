#include "Student.h"

// Constructor
//Student::Student(const std::string& identifier, const std::string& given_name, const std::string& family_name, const std::string& email, const std::map<std::string, std::vector<double>>& grades, const std::map<std::string, CourseResult>& results) : given_name(given_name), family_name(family_name), grades(grades), results(results) {
//
//	if (validateIdentifier(identifier).size() == 0) {
//		throw std::runtime_error("Identifier " + identifier + " is invalid."); // Log error.
//	}
//
//	if (validateEmail(email).size() == 0) {
//		throw std::runtime_error("Email " + email + " is invalid."); // Log error.
//	}
//
//};

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

void Student::populateResults(const CourseHolder& courses) {

	//// Print out result and total score.
	//auto associated_course_result_object = (*map_to_course_ptrs[pair.first]).getGrade(pair.second);

	//std::wcout << L" " << stringRound(associated_course_result_object.getScore()) << L" ┃";
	//std::wcout << L" " << (*map_to_course_ptrs[pair.first]).getNumberOfCredits() << L"    ┃";

	//// Used in extra misc information table.
	//all_marks.push_back(associated_course_result_object.getScore());
	//bool result_bool = associated_course_result_object.getResult();

	for (const auto& pair : courses.getCourseMap()) {
		if (grades.count((*pair.second).getIdentifier())) {
			CourseResult cr = (*pair.second).getGrade(grades.at((*pair.second).getIdentifier()));
			results.insert({ (*pair.second).getIdentifier(), cr });
		}
	}
	
}

const std::map<std::string, CourseResult> Student::getResults() const {
	return results;
}

const bool Student::getCourseGrades(const std::string& course_code, std::vector<double>* course_grades) const {

	auto tmp = getGrades();

	if (tmp.count(course_code)) {
		*course_grades = getGrades().at(course_code);
		return true;
	} else {
		//std::cout << getGivenName() + " " + getFamilyName() + " does not take " + courseCode + "." + '\n'; // Log
		return false;
	}

}

const bool Student::needsResit() const {
	for (const auto& pair : getResults()) {
		if (!pair.second.getResult()) { return true; }
	}
	return false;
}

const std::smatch Student::validateIdentifier() const {
	std::regex regular_expression("^([A-Z]{2})([0-9]{8})$");
	std::smatch match;
	if (!std::regex_search(identifier, match, regular_expression)) { } // REMOVE ME!!!!!!!!!!!
	return match;
}

const std::smatch Student::validateEmail() const {
	// Regex magic because emails have a ton of edge cases.
	// https://stackoverflow.com/questions/201323/how-can-i-validate-an-email-address-using-a-regular-expression
	std::regex regular_expression(R"((?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9]))\.){3}(?:(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9]?[0-9])|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\]))");
	std::smatch match;

	if (!std::regex_search(email, match, regular_expression)) { } // REMOVE ME!!!!!!!!!!!

	return match;
}

const bool Student::validateGrades() const {

	for (const auto& pair : grades) {
		for (const auto& score : pair.second) {
			if ((score < 0) || (score > 100)) {
				return false;
			}
		}
	}

	return true;
}