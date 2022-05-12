#include "Student.h"

using json = nlohmann::json;

StudentHolder::StudentHolder(std::string file_path_name) {
	std::ifstream json_file(file_path_name);
	std::vector<json> students_json = json::parse(json_file);
	std::vector<Student> students;
	for (const auto& student : students_json) {
		students.push_back((Student)student);
	}
}

// Constructor
Student::Student(std::string identifier, std::string givenName, std::string familyName, std::string email, std::map<std::string, std::vector<double>> grades, std::map<std::string, CourseResult> results) :
	identifier(identifier), givenName(givenName), familyName(familyName), email(email), grades(grades), results(results) {};

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

std::smatch Student::validateIdentifier()
{
	std::regex regular_expression("^([A-Z]{2})([0-9]{8})$");
	std::smatch match;
	if (regex_search(identifier, match, regular_expression))
	{
		return match;
	}
	else
	{
		std::cout << "Invalid identifier.";
	}
}

std::smatch Student::validateEmail() {
	std::regex regular_expression("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	std::smatch match;
	if (regex_search(email, match, regular_expression)) {
		return match;
	}
	
	std::cout << "Invalid email."; // Logger.
	throw std::invalid_argument("Invalid email provided.");
	// Ask James: Why not return bool instead? Invalid control path.
}


