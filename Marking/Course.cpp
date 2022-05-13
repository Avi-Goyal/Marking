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
	return CourseType::ExamOnlyCourse;
}

double CourseworkOnly::getGrade() {
	return CourseType::CourseworkOnlyCourse;
}

double Hybrid::getGrade() {
	return CourseType::HybridCourse;
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

	// Smart pointers should be used - James.
	for (const auto& course : courses_json) {

		Course* ptr;
		
		switch ((int)course.at("courseType"))
		{
		case CourseType::ExamOnlyCourse:
			ptr = new ExamOnly(course);
			break;
		case CourseType::CourseworkOnlyCourse:
			ptr = new CourseworkOnly(course);
			break;
		case CourseType::HybridCourse:
			ptr = new CourseworkOnly(course);
			break;
		default:
			// Log.
			throw std::invalid_argument("Course type is invalid.");
		}

		std::string course_id = course.at("identifier");
		map_id_to_student[course_id] = ptr;

		}
	}


// Read # of students/courses should be logged.
// 

Course* CourseHolder::getCourse(std::string course_code) {
	return map_id_to_student[course_code];
}

//CourseHolder::CourseHolder(std::vector<Course*> courses) : courses(courses) { }
