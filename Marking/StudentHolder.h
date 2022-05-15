#pragma once
#include <map>
#include <string>
#include <memory>
#include <locale>
#include <iomanip>
#include <windows.h> // ask james
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <string>
#include <codecvt>
#include "Course.h"
#include "Student.h"
#include <plog/Log.h> // DO not comment this out or unicode support will break. Ask James, truly weird behaviour...


class StudentHolder {
private:
	std::vector<Student> students;
	std::map <std::string, Student> map_id_to_student;
public:
	// Constructors.
	StudentHolder(const std::string& file_path_name);


	Student getStudent(const std::string& student_id);

	StudentHolder() = default;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(StudentHolder, students);

	std::vector<double> getGrades(const std::string& student_id, const std::string& course_id);
	std::map<std::string, Student> getStudentMap();


	void niceOutput(const std::string&  student_id, const CourseHolder& courses);

	//void saveAsJsonFile(Student a_student);

};

