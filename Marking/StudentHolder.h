#pragma once
#include <map>
#include <string>
#include <memory>
#include "Course.h"
#include "Student.h"

class StudentHolder
{
private:
	std::vector<Student> students;
	std::map < std::string, Student > map_id_to_student;
public:
	// Constructors.
	StudentHolder(std::string file_path_name);


	Student getStudent(std::string student_id);

	StudentHolder() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(StudentHolder, students);

	std::vector<double> getGrades(std::string const& student_id, std::string const& course_id);

};

