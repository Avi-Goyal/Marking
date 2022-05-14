#include "CourseHolder.h"
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
		map_id_to_course[course_id] = ptr;
		map_id_to_name[course_id] = course.at("name");
	}
}

std::map<std::string, std::shared_ptr<Course>> CourseHolder::getCourseMap()
{
	return map_id_to_course;
}

// Read # of students/courses should be logged.
std::shared_ptr<Course> CourseHolder::getCourse(std::string course_code) {
	return map_id_to_course[course_code];
}

std::string CourseHolder::getCourseName(const std::string& course_code) {
	return map_id_to_name.at(course_code);
}