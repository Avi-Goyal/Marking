#pragma once
#include <string>
#include <iostream>
#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include <regex>
#include <fstream>
#include "CourseResult.h"

// Abstract base class.
class Course {
protected:
	std::string identifier;
	std::vector<double> weights;
	enum numberOfCredits {
		TenCredits, TwentyCredits
	};
public:
	virtual CourseResult getGrade(std::vector<double> grades) = 0;
	virtual std::vector<double> getWeights() = 0;
	Course() = default;
};

// Callable classes.
class ExamOnly : public Course {
public:
	CourseResult getGrade(std::vector<double> grades);
	std::vector<double> getWeights();
	ExamOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ExamOnly, identifier, weights);
};

class CourseworkOnly : public Course {
public:
	CourseResult getGrade(std::vector<double> grades);
	std::vector<double> getWeights();
	CourseworkOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CourseworkOnly, identifier, weights);
};

class Hybrid : public Course {
public:
	CourseResult getGrade(std::vector<double> grades);
	std::vector<double> getWeights();
	Hybrid() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Hybrid, identifier, weights);
}; 

