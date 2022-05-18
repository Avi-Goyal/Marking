#include "CourseHolder.h"
#include "Course.h"
#include "Student.h"

CourseHolder::CourseHolder() {}

CourseHolder::CourseHolder(const std::string& file_path_name) {

	using json = nlohmann::json;

	std::ifstream json_file(file_path_name);
	std::vector<json> courses_json = json::parse(json_file);

	for (const auto& course : courses_json) {

		/// We store shared smart pointers so that we can copy them from our map
		/// without issue given that unique_ptr can only be moved, not copied. This also
		/// means that we do not need to set up a destructor for CourseHolder as when
		/// the map is destroyed the pointers destructor will be called automatically
		/// and free the memory allocated on the heap.
		std::shared_ptr<Course> ptr;

		int course_type = course.at("course_type");

		switch (course_type)
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
			plog::init(plog::info, "Log.txt");
			LOG(plog::fatal) << "Course type " << course_type << " loaded from json is invalid for course " << (std::string)course.at("identifier");
			throw std::invalid_argument("Course type is invalid. See log.txt for details.");
		}

		std::string course_id = course.at("identifier");
		map_id_to_course[course_id] = ptr;
		map_id_to_name[course_id] = course.at("name");
	}

	json_file.close();
}

const std::map<std::string, std::shared_ptr<Course>> CourseHolder::getCourseMap() const {
	return map_id_to_course;
}

const std::shared_ptr<Course> CourseHolder::getCourse(const std::string& course_code) const {
	return map_id_to_course.at(course_code);
}

const std::string CourseHolder::getCourseName(const std::string& course_code) const {
	return map_id_to_name.at(course_code);
}