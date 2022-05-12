#include "Course.h"


double Course::getGrade() { return 1.0; }

Course::Course(std::string identifier, std::vector<double> weights) : identifier(identifier) {
	double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
	if (sum_of_weights != 1.0) { std::cout << "ERROR: Weights invalid." << std::endl; }
}

ExamOnly::ExamOnly(std::string identifier_t, std::vector<double> weights_t) {
    double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
    if (sum_of_weights != 1.0) { 
		std::cout << "ERROR: Weights invalid." << std::endl; // Replace with logger later.
		weights = weights_t;
	}
	identifier = identifier_t;
}

double ExamOnly::getGrade() {
	return 0.0;
}

Hybrid::Hybrid(std::string identifier_t, std::vector<double> weights_t) {
	double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
	if (sum_of_weights != 1.0) {
		std::cout << "ERROR: Weights invalid." << std::endl; // Replace with logger later.
		weights = weights_t;
	}
	identifier = identifier_t;
}

double Hybrid::getGrade() {
	return 0.0;
}

CourseworkOnly::CourseworkOnly(std::string identifier_t, std::vector<double> weights_t) {
	double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
	if (sum_of_weights != 1.0) {
		std::cout << "ERROR: Weights invalid." << std::endl; // Replace with logger later.
		weights = weights_t;
	}
	identifier = identifier_t;
}

double CourseworkOnly::getGrade() {
	return 0.0;
}

CourseHolder::CourseHolder(std::string file_path_name) {
	std::ifstream json_file(file_path_name);
	std::vector<json> courses_json = json::parse(json_file);
	std::vector<Course*> courses;
	for (const auto& course : courses_json) {
		
		int course_type = course.at("courseType");

		if (course_type == 0) {
			Course* ptr = new ExamOnly();
			courses.push_back(ptr);
		}
		else if (course_type == 1) {
			Course* ptr = new CourseworkOnly();
			courses.push_back(ptr);
		}
		else if (course_type == 2) {
			Course* ptr = new Hybrid();
			courses.push_back(ptr);
		}
		else {
			throw std::invalid_argument("Course type is invalid.");
		}
	}
	this->courses = courses;
}

CourseHolder::CourseHolder(std::vector<Course*> courses) : courses(courses) { }
