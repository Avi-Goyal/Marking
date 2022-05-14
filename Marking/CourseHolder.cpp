#include "CourseHolder.h"
#include "Course.h"
#include "Student.h"

CourseHolder::CourseHolder(std::string file_path_name) {

	using json = nlohmann::json;

	std::ifstream json_file(file_path_name);
	std::vector<json> courses_json = json::parse(json_file);

	for (const auto& course : courses_json) {

		/// We store shared smart pointers so that we can copy them from our map
		/// without issue given that unique_ptr can only be moved, not copied. This also
		/// means that we do not need to set up a destructor for CourseHolder as when
		/// the map is destroyed the pointers destructor will be called automatically.
		std::shared_ptr<Course> ptr;

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

/// This is rather dangerous because of shared_ptr, we should try get rid of this.
/// Create a custom iterator on course so that we don't need to give this out.
const std::map<std::string, std::shared_ptr<Course>> CourseHolder::getCourseMap() {
	return map_id_to_course;
}

// Read # of students/courses should be logged.
std::shared_ptr<Course> CourseHolder::getCourse(std::string course_code) {
	return map_id_to_course[course_code];
}

std::string CourseHolder::getCourseName(const std::string& course_code) {
	return map_id_to_name[course_code];
}