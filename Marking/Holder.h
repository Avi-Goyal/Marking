#pragma once
#include <map>
#include <string>
#include <memory>
#include "Course.h"
#include "Student.h"

enum CourseType {
	ExamOnlyCourse = 0,
	CourseworkOnlyCourse = 1,
	HybridCourse = 2
};

class CourseHolder {
private:
	std::map<std::string, std::shared_ptr<Course>> map_id_to_student;
public:
	//CourseHolder(std::vector<Course*> courses);
	CourseHolder(std::string file_path_name);

	std::shared_ptr<Course> getCourse(std::string course_code);
};


class StudentHolder
{
private:
	std::vector<Student> students;
public:
	// Constructors.
	StudentHolder(std::string file_path_name);

	std::map < std::string, Student > map_id_to_student;
	Student getStudent(std::string student_id);

	StudentHolder() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(StudentHolder, students);

	std::vector<double> getGrades(std::string const& student_id, std::string const& course_id);
};

