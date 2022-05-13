#include "Holder.h"
#include "Course.h"
#include "Student.h"

CourseHolder::CourseHolder(std::string file_path_name) {

	using json = nlohmann::json;

	std::ifstream json_file(file_path_name);
	std::vector<json> courses_json = json::parse(json_file);

	// Smart pointers should be used - James.
	for (const auto& course : courses_json) {

		std::shared_ptr<Course> ptr;
		//Course* ptr;

		switch ((int)course.at("courseType"))
		{
		case CourseType::ExamOnlyCourse:
			ptr = std::make_shared<ExamOnly>(course);
			break;
		case CourseType::CourseworkOnlyCourse:
			ptr = std::make_shared<CourseworkOnly>(course);
			break;
		case CourseType::HybridCourse:
			ptr = std::make_shared<Hybrid>(course);
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
std::shared_ptr<Course> CourseHolder::getCourse(std::string course_code) {
	return map_id_to_student[course_code];
}

StudentHolder::StudentHolder(std::string file_path_name) {
	std::ifstream json_file(file_path_name);
	students = json::parse(json_file);
	for (const auto& tmp_student : students) {
		map_id_to_student[tmp_student.identifier] = tmp_student;
	}
}

Student StudentHolder::getStudent(std::string student_id) {
	return map_id_to_student[student_id];
}

std::vector<double> StudentHolder::getGrades(std::string const& student_id, std::string const& course_id) {
	return this->getStudent(student_id).getGrades().at(course_id);
}
