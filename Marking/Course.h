#include <string>
#include <iostream>
#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include <regex>
#include <fstream>

using json = nlohmann::json;

// This is the abstract base class, therefore it has no constructor.
class Course {
public:
    std::string identifier;
    std::vector<double> weights;

	virtual double getGrade() = 0;

	Course() = default;
	
protected:
	Course(std::string identifier, std::vector<double> weights);
};

// Callable classes.
class ExamOnly : public Course {
public:
    ExamOnly(std::string identifier, std::vector<double> weights);
	double getGrade();
	ExamOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ExamOnly, identifier, weights);
};

class CourseworkOnly : public Course {
public:
    CourseworkOnly(std::string identifier, std::vector<double> weights);
	double getGrade();
	CourseworkOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CourseworkOnly, identifier, weights);
};

class Hybrid : public Course {
public:
	Hybrid(std::string identifier, std::vector<double> weights);
	double getGrade();
	Hybrid() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Hybrid, identifier, weights);
}; 

class CourseHolder {
//private:
	
public:
	std::vector<Course*> courses;
	CourseHolder(std::vector<Course*> courses);
	// constrcutor from json file
	CourseHolder(std::string file_path_name);
	CourseHolder() = default;
	//NLOHMANN_DEFINE_TYPE_INTRUSIVE(CourseHolder, courses);
};

