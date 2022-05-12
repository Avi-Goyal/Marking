#include "Course.h"

double Course::getGrade() { return 1.0; }

//Course::Course(std::string identifier, std::vector<double> weights) : identifier(identifier) {
//	double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
//	if (sum_of_weights != 1.0) { std::cout << "ERROR: Weights invalid." << std::endl; }
//}

//ExamOnly::ExamOnly(std::string identifier_t, std::vector<double> weights_t) {
//    double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
//    if (sum_of_weights != 1.0) { 
//		std::cout << "ERROR: Weights invalid." << std::endl; // Replace with logger later.
//		weights = weights_t;
//	}
//	identifier = identifier_t;
//}

//Hybrid::Hybrid(std::string identifier_t, std::vector<double> weights_t) {
//	double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
//	if (sum_of_weights != 1.0) {
//		std::cout << "ERROR: Weights invalid." << std::endl; // Replace with logger later.
//		weights = weights_t;
//	}
//	identifier = identifier_t;
//}

double ExamOnly::getGrade() {
	return 0.0;
}

double CourseworkOnly::getGrade() {
	return 1.0;
}

double Hybrid::getGrade() {
	return 2.0;
}

std::vector<double> ExamOnly::getWeights() {
	return weights;
}

std::vector<double> CourseworkOnly::getWeights() {
	return weights;
}

std::vector<double> Hybrid::getWeights() {
	return weights;
}

//CourseworkOnly::CourseworkOnly(std::string identifier_t, std::vector<double> weights_t) {
//	double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
//	if (sum_of_weights != 1.0) {
//		std::cout << "ERROR: Weights invalid." << std::endl; // Replace with logger later.
//		weights = weights_t;
//	}
//	identifier = identifier_t;
//}



CourseHolder::CourseHolder(std::string file_path_name) {

	using json = nlohmann::json;

	std::ifstream json_file(file_path_name);
	std::vector<json> courses_json = json::parse(json_file);

	for (const auto& course : courses_json) {
		
		int course_type = course.at("courseType");
		std::string course_id = course.at("identifier");

		if (course_type == 0) {
			Course* ptr = new ExamOnly(course);
			map_id_to_student[course_id] = ptr;
		}
		else if (course_type == 1) {
			Course* ptr = new CourseworkOnly(course);
			map_id_to_student[course_id] = ptr;
		}
		else if (course_type == 2) {
			Course* ptr = new Hybrid(course);
			map_id_to_student[course_id] = ptr;
		}
		else {
			throw std::invalid_argument("Course type is invalid.");
		}

	}
}

Course* CourseHolder::getCourse(std::string course_code) {
	return map_id_to_student[course_code];
}

//CourseHolder::CourseHolder(std::vector<Course*> courses) : courses(courses) { }
