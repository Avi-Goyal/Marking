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
#include <cstdlib>
#include <codecvt>
#include "Course.h"
#include "Student.h"
#include <plog/Log.h> // DO not comment this out or unicode support will break. Ask James, truly weird behaviour...

const class StudentHolder {
private:
	// Internal variables.
	std::vector<Student> students;
	std::map<std::string, Student> map_id_to_student;
public:
	// Constructor.
	StudentHolder(const std::string& file_path_name);
	StudentHolder();

	// Methods.
	const Student getStudent(const std::string& student_id) const;
	const std::vector<double> getGrades(const std::string& student_id, const std::string& course_id) const;
	const std::map<std::string, Student> getStudentMap() const;
	void niceOutput(const std::string& student_id, const CourseHolder& courses) const;
	//void saveAsJsonFile(Student a_student);
};

