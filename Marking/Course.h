#pragma once
#include <string>
#include <iostream>
#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include <regex>
#include <fstream>
#include <numeric>
#include <functional>
#include <plog/Log.h>
#include "CourseResult.h"


enum Credits {
	TenCredits = 10, TwentyCredits = 20
};

// Abstract base class.
class Course {
protected:
	std::string identifier;
	std::vector<double> weights;
	Credits numberOfCredits;
public:
	virtual CourseResult getGrade(std::vector<double> grades) = 0;
	virtual std::vector<double> getWeights() = 0;
	virtual Credits getNumberOfCredits() = 0;
	Course() = default;
};

// Callable classes.
class ExamOnly : public Course {
public:
	CourseResult getGrade(std::vector<double> grades);
	std::vector<double> getWeights();
	Credits getNumberOfCredits();
	ExamOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ExamOnly, identifier, weights, numberOfCredits);
};

class CourseworkOnly : public Course {
public:
	CourseResult getGrade(std::vector<double> grades);
	std::vector<double> getWeights();
	Credits getNumberOfCredits();
	CourseworkOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CourseworkOnly, identifier, weights, numberOfCredits);
};

class Hybrid : public Course {
public:
	CourseResult getGrade(std::vector<double> grades);
	std::vector<double> getWeights();
	Credits getNumberOfCredits();
	Hybrid() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Hybrid, identifier, weights, numberOfCredits);
}; 

