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
	CreateCourseHolder(file_path_name);
}

CourseHolder::CourseHolder(std::vector<Course*> courses) : courses(courses) { }

// Static 
CourseHolder CreateCourseHolder(std::string file_path_name) {
	std::ifstream json_file(file_path_name);
	std::vector<json> courses_json = json::parse(json_file);
	std::vector<Course*> courses;
	for (const auto& course : courses_json) {

		if (course.at("courseType") == 0) {
			Course* ptr = new ExamOnly();
			courses.push_back((ExamOnly*) ptr);

		} else if (course.at("courseType") == 1) {
			Course* ptr = new ExamOnly();
			courses.push_back((CourseworkOnly*) ptr);

		} else if (course.at("courseType") == 2) {
			Course* ptr = new ExamOnly();
			courses.push_back((Hybrid*) ptr);
		}

		throw std::invalid_argument("Course type is invalid.");
	}

	return CourseHolder(courses);
}