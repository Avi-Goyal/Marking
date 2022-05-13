#include <string>
#include <iostream>
#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include <regex>
#include <fstream>

// Abstract base class.
class Course {
public:
    std::string identifier;
    std::vector<double> weights;

	virtual double getGrade() = 0;
	virtual std::vector<double> getWeights() = 0;
	Course() = default;
	
	//Course(std::string identifier, std::vector<double> weights);
};

// Callable classes.
class ExamOnly : public Course {
public:
    //ExamOnly(std::string identifier, std::vector<double> weights);
	double getGrade();
	std::vector<double> getWeights();
	ExamOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ExamOnly, identifier, weights);
};

class CourseworkOnly : public Course {
public:
    //CourseworkOnly(std::string identifier, std::vector<double> weights);
	double getGrade();
	std::vector<double> getWeights();
	CourseworkOnly() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CourseworkOnly, identifier, weights);
};

class Hybrid : public Course {
public:
	//Hybrid(std::string identifier, std::vector<double> weights);
	double getGrade();
	std::vector<double> getWeights();
	Hybrid() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Hybrid, identifier, weights);
}; 

class CourseHolder {
private:
	std::map<std::string, Course*> map_id_to_student;
public:
	//CourseHolder(std::vector<Course*> courses);
	CourseHolder(std::string file_path_name);

	Course* getCourse(std::string course_code);
};

