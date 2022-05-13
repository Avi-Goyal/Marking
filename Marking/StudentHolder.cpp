#include "StudentHolder.h"
#include "Course.h"
#include "Student.h"

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
