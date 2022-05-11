#include "Student.h"


Student::Student(std::string identifier, std::string givenName, std::string familyName, std::string email, std::map<std::string, std::vector<double>> grades, std::map<std::string, CourseResult> results) :
    identifier(identifier), givenName(givenName), familyName(familyName), email(email), grades(grades), results(results) {};


Student::Student(const std::string& file_path_name)
{
    using json = nlohmann::json;

    // opening file using fstream
    std::ifstream json_file(file_path_name);

    // parse the json file into json object
    json json_object = json::parse(json_file);

    // construct student object from json object key values
    this->identifier = json_object.value("identifier", "what");
    this->givenName = json_object.value("givenName", "what");
    this->familyName = json_object.value("familyName", "what");
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

std::smatch Student::validateIdentifier(const std::string& identifier)
{
    std::regex regular_expression("^([A-Z]{2})([0-9]{8})$");
    std::smatch match;
    if (regex_search(identifier, match, regular_expression))
    {
        std::cout << "Valid identifier.";
        return match;
    }
    else
    {
        std::cout << "Invalid identifier.";
    }
}

std::smatch Student::validateEmail(const std::string& email)
{
    std::regex regular_expression("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    std::smatch match;
    if (regex_search(email, match, regular_expression))
    {
        std::cout << "Valid email.";
        return match;
    }
    else
    {
        std::cout << "Invalid email.";
    }

}