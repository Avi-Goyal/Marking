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
	void print_vector(std::vector<double> const& v)
	{
		for (int i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
	}
	std::string bool_names(bool const& true_or_false) {

		return (true_or_false == 1 ? "Passed." : "Failed.");
	}
	
public:
	// Constructors.
	StudentHolder(std::string file_path_name);


	Student getStudent(std::string student_id);

	StudentHolder() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(StudentHolder, students);

	std::vector<double> getGrades(std::string const& student_id, std::string const& course_id);
	std::map<std::string, Student> getStudentMap();

	// nicely formatte output
	void niceOutput(std::string const& student_id, CourseHolder courses);

	void saveAsJsonFile(Student a_student);

};

