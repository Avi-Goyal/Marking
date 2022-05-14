#include "StudentHolder.h"
#include "Course.h"
#include "Student.h"
#include<locale>
#include<iomanip>
#include <windows.h>

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

std::map<std::string, Student> StudentHolder::getStudentMap() {
	return map_id_to_student;
}

void StudentHolder::niceOutput(std::string const& student_id, CourseHolder courses)
{
    // or use simpler but less nice system:
	//system("Color E0");

	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 7);
	Student a_student = getStudent(student_id);
	std::map<std::string, std::vector<double>> map_course_to_grades = a_student.getGrades();
	
	std::cout << "Student full name: " + a_student.getGivenName() + " " + a_student.getFamilyName() + '\n' + '\n' + 
		a_student.getGivenName() + " " + a_student.getFamilyName() + "'s email address: " + a_student.getEmail() + '\n' + '\n' +
		a_student.getGivenName() + " " + a_student.getFamilyName() + "'s grades:" + '\n';
	for (auto const& pair : map_course_to_grades) {
		std::cout << pair.first << ": { "; print_vector(pair.second); std::cout << "}" << '\n';
	}
	std::cout << '\n';
	a_student.populateResults(courses);
	
	std::cout << a_student.getGivenName() + " " + a_student.getFamilyName() + "'s course results:" + '\n';
	for (auto pairs : a_student.getResults()) {
		std::cout << courses.getCourseName(pairs.first) << '\n';
		std::cout << "Score: " << pairs.second.getScore() << '\n' << "Result: ";
		if (pairs.second.getResult() == 0){
			SetConsoleTextAttribute(console_color, BACKGROUND_RED | 7);
		} 
		else {
			SetConsoleTextAttribute(console_color, BACKGROUND_GREEN | 0);
		}
		std::cout << bool_names(pairs.second.getResult());
		SetConsoleTextAttribute(console_color, 7);
		std::cout << std::endl << std::endl;
	}
	system("pause>0");
}

void StudentHolder::saveAsJsonFile(Student a_student) {

	a_student.getResults();
	json a_json_student = a_student;
	std::map<std::string, double> map;
	json json_results;
	for (auto some : a_student.getResults()) {
		json_results[some.first] = { some.second.getScore(), bool_names(some.second.getResult()) };
	}

	std::ofstream file("student_results.json");
	file << a_json_student << "," << json_results;
}
