#include "Student.h"

using json = nlohmann::json;

StudentHolder::StudentHolder(std::string file_path_name) {
	std::ifstream json_file(file_path_name);
	std::vector<json> students_json = json::parse(json_file);
	for (const auto& student : students_json) {
		Student tmp_student = (Student)student;
		students.push_back(tmp_student);
		map_id_to_student[student.at("identifier")] = tmp_student;
	}
}

Student StudentHolder::getStudent(std::string student_id) {
	return map_id_to_student[student_id];
}

// Constructor
Student::Student(std::string tmp_identifier, std::string givenName, std::string familyName, std::string tmp_email, std::map<std::string, std::vector<double>> grades, std::map<std::string, CourseResult> results) : givenName(givenName), familyName(familyName), email(email), grades(grades), results(results) {

	if (validateIdentifier(tmp_identifier)) {
		identifier = tmp_identifier;
	} else {
		throw std::runtime_error("Identifier " + tmp_identifier + " is invalid.");
	}

	if (validateEmail(tmp_email)) {
		identifier = tmp_email;
	} else {
		throw std::runtime_error("Email " + tmp_email + " is invalid.");
	}

};

std::string Student::getIdentifier()
{
	return identifier;
}

std::string Student::getGivenName()
{
	return givenName;
}

std::string Student::getFamilyName()
{
	return familyName;
}

std::string Student::getEmail()
{
	return email;
}

std::map<std::string, std::vector<double>> Student::getGrades()
{
	return grades;
}

std::map<std::string, CourseResult> Student::getResults()
{
	return results = results;
}

// Ask James about std::smatch being returned.
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

