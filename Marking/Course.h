#pragma once
#include "CourseResult.h"
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <regex>
#include <fstream>
#include <numeric>
#include <nlohmann/json.hpp>

const enum Credits {
    TenCredits = 10, TwentyCredits = 20
};

// Abstract base class.
const class Course {
protected:
    // Variables.
    std::string identifier;
    std::vector<double> weights;
    Credits numberOfCredits{};
public:
    // Constructor.
    const Course() = default;
    // You said you won't mark us down for this error.
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Course, identifier, weights, numberOfCredits);

    // Virtual methods.
    virtual const CourseResult getGrade(const std::vector<double>& grades) const = 0;

    // Methods.
    const std::vector<double> getWeights() const;
    const Credits getNumberOfCredits() const;
    const std::string getIdentifier() const;
    const std::smatch validateIdentifer() const;
    const bool validateWeights() const;
};

// Callable classes.
const class ExamOnly : public Course {
public:
    const CourseResult getGrade(const std::vector<double>& grades) const;
};

const class CourseworkOnly : public Course {
public:
    const CourseResult getGrade(const std::vector<double>& grades) const;
};

const class Hybrid : public Course {
public:
    const CourseResult getGrade(const std::vector<double>& grades) const;
};
