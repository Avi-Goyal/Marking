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
//#include <plog/Log.h>
#include "CourseResult.h"

// Why do we even need this? Making it a class loses enum -> int conversion. Ask James.
const enum Credits {
	TenCredits = 10, TwentyCredits = 20
};

// Abstract base class.
const class Course {
protected:
	// Variables.
	std::string identifier;
	std::vector<double> weights;
	Credits numberOfCredits;
public:
	// Constructor.
	const Course() = default;
	
	// Methods.
	virtual const CourseResult getGrade(const std::vector<double>& grades) const = 0; // Why needed (compiler throws a fit when removed)? Ask James.
	const std::vector<double> getWeights() const;
	const Credits getNumberOfCredits() const;
};

// Callable classes.
const class ExamOnly : public Course {
public:
	const CourseResult getGrade(const std::vector<double>& grades) const;
	const ExamOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ExamOnly, identifier, weights, numberOfCredits);
};

const class CourseworkOnly : public Course {
public:
	const CourseResult getGrade(const std::vector<double>& grades) const;
	const CourseworkOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CourseworkOnly, identifier, weights, numberOfCredits);
};

const class Hybrid : public Course {
public:
	const CourseResult getGrade(const std::vector<double>& grades) const;
	const Hybrid() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Hybrid, identifier, weights, numberOfCredits);
};
