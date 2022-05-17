#include "Student.h"

const std::string Student::getIdentifier() const {
	return identifier;
}

const std::string Student::getGivenName() const {
	return given_name;
}

const std::string Student::getFamilyName() const {
	return family_name;
}

const std::string Student::getFullName() const {
	return given_name + " " + family_name;
}

const std::string Student::getEmail() const {
	return email;
}

const std::map<std::string, std::vector<double>> Student::getGrades() const {
	return grades;
}

void Student::populateResults(const CourseHolder& courses) {

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
		plog::init(plog::info, "Log.txt");
		LOG(plog::warning) << getFullName() + " does not take " + course_code;
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
	std::regex_search(identifier, match, regular_expression);
	return match;
}

const std::smatch Student::validateEmail() const {
	std::regex regular_expression(R"(^[^@\s]+@[^@\s]+\.[^@\s]+$)");
	std::smatch match;
	std::regex_search(email, match, regular_expression);
	return match;
}

const bool Student::validateGrades() const {

	for (const auto& pair : grades) {
		for (const auto& score : pair.second) {
			if (!((0 <= score) && (score <= 100))) {
			std::wcout << score << std::endl;
				LOG(plog::warning) << "Grades for " + getFullName() + " has failed on validating scores. All scores must be 0 <= score <= 100.";
				return false;
			}
		}
	}

	return true;
}