#include "Student.h"

// Utility Functions.
bool validateIdentifier(const std::string& identifier) {
    std::regex regular_expression("^([A-Z]{2})([0-9]{8})$");
    std::smatch match;
    return (regex_search(identifier, match, regular_expression));
}

bool validateEmail(const std::string& email) {
    std::regex regular_expression("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    std::smatch match;
    return regex_search(email, match, regular_expression);
}

Student::Student(const std::string tmp_identifier,
    const std::string given_name,
    const std::string family_name,
    const std::string tmp_email,
    const std::map<std::string, std::vector<double>> grades,
    const std::map<std::string, CourseResult> results) :
    given_name(given_name), family_name(family_name), grades(grades), results(results) {

    // Validation checks.
    if (validateIdentifier(tmp_identifier)) {
        identifier = tmp_identifier;
    }
    else {
        throw std::invalid_argument("Identifier provided \"" + tmp_identifier + "\" is invalid.");
    }

    if (validateEmail(tmp_email)) {
        email = tmp_email;
    }
    else {
        throw std::invalid_argument("Email provided \"" + tmp_identifier + "\" is invalid.");
    }
}


Student::Student(const std::string& file_path_name) {
    using json = nlohmann::json;

    // Opening file using fstream.
    std::ifstream json_file(file_path_name);

    // Parse the json file into json object.
    json json_object = json::parse(json_file);

    // Construct student object from json object key values.
    this->identifier = json_object.value("identifier", "what");
    this->given_name = json_object.value("givenName", "what");
    this->family_name = json_object.value("familyName", "what");
    this->email = json_object.value("email", "what");
    json j1;
    this->grades = json_object.value("grades", j1);
    this->results = results;
}

std::string Student::getIdentifier()
{
    return identifier;
}

std::string Student::getGivenName()
{
    return given_name;
}

std::string Student::getFamilyName()
{
    return family_name;
}

std::string Student::getEmail()
{
    return email;
}

bool Student::getGrades(std::string course_code, std::vector<double>* grades) {
//    *grades = courseHolder[course_code];
    return true;
}

std::map<std::string, CourseResult> Student::getResults() {
    return results;
}
