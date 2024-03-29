#pragma once
#include <map>
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "CourseResult.h"
#include "CourseHolder.h"

const class Student {
 private:
    // Variables:
    std::string identifier{}, given_name{}, family_name{}, email{};
    std::map<std::string, std::vector<double>> grades{};
    std::map<std::string, CourseResult> results;
 public:
    // Constructors.
    Student() = default;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Student, identifier, given_name, family_name, email, grades);

    // Methods.
    const std::string getIdentifier() const;
    const std::string getGivenName() const;
    const std::string getFullName() const;
    const std::string getFamilyName() const;
    const std::string getEmail() const;
    const std::map<std::string, std::vector<double>> getGrades() const;
    void populateResults(const CourseHolder& courses);
    const std::map<std::string, CourseResult> getResults() const;
    const bool getCourseGrades(const std::string& courseCode, std::vector<double>* course_grades) const;
    const bool needsResit() const;
    const std::smatch validateIdentifier() const;
    const std::smatch validateEmail() const;
    const bool validateGrades() const;
};
