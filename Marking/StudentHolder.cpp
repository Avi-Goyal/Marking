#include "StudentHolder.h"
#include "Course.h"
#include "Student.h"


// Utility functions to facilitate niceOutput.
std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> strconverter;
std::wstring toUnicodeString(std::string str) {
	return strconverter.from_bytes(str);
}

void operator<<(std::wostream& wostream, std::string str) {
	wostream << toUnicodeString(str);
}

std::wstring stringRound(double grade) {
	double rounded_grade = round(grade);
	std::string rounded_string_grade = std::to_string(grade);

	if (rounded_string_grade.size() > 5) {
		std::string tmp = rounded_string_grade.substr(0, 5);
		return toUnicodeString(tmp);
	}

	return toUnicodeString(rounded_string_grade);
}

StudentHolder::StudentHolder(const std::string& file_path_name) {

	std::ifstream json_file(file_path_name);
	students = json::parse(json_file);

	for (const auto& tmp_student : students) {
		map_id_to_student[tmp_student.identifier] = tmp_student;
	}
}

Student StudentHolder::getStudent(const std::string& student_id) {
	return map_id_to_student[student_id];
}

std::vector<double> StudentHolder::getGrades(const std::string& student_id, const std::string& course_id) {
	return this->getStudent(student_id).getGrades().at(course_id);
}

std::map<std::string, Student> StudentHolder::getStudentMap() {
	return map_id_to_student;
}

void StudentHolder::niceOutput(const std::string& student_id, const CourseHolder& courses) {

	// Magic function that allows unicode in console. Code works on uni computers and at home, no idea why compiler doesn't like it.
	_setmode(_fileno(stdout), _O_U8TEXT);

	// Setup special colour handling.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	Student student_to_output = map_id_to_student[student_id];

	std::wstring tmp_full_name = toUnicodeString(student_to_output.getGivenName() + " " + student_to_output.getFamilyName());
	std::wstring tmp_identifier = toUnicodeString(student_to_output.getIdentifier());
	std::wstring tmp_email = toUnicodeString(student_to_output.getEmail());

	std::vector<size_t> vector_of_strings = { tmp_identifier.size(), tmp_full_name.size(), tmp_email.size() };
	size_t max_size_string = *std::max_element(vector_of_strings.begin(), vector_of_strings.end());

	std::wcout << L"┏━━━━━━━━━━━━┳━" << std::wstring(max_size_string, L'━') << L"━┓" << std::endl;
	std::wcout << L"┃ Student ID ┃ " << tmp_identifier << std::wstring(1 + max_size_string - tmp_identifier.size(), ' ') << L"┃" << std::endl;
	std::wcout << L"┣━━━━━━━━━━━━╋━" << std::wstring(max_size_string, L'━') << L"━┫" << std::endl;
	std::wcout << L"┃ Full Name  ┃ " << tmp_full_name << std::wstring(1 + max_size_string - tmp_full_name.size(), ' ') << L"┃" << std::endl;
	std::wcout << L"┣━━━━━━━━━━━━╋━" << std::wstring(max_size_string, L'━') << L"━┫" << std::endl;
	std::wcout << L"┃ Email      ┃ " << tmp_email << std::wstring(1 + max_size_string - tmp_email.size(), ' ') << L"┃" << std::endl;
	std::wcout << L"┗━━━━━━━━━━━━┻━" << std::wstring(max_size_string, L'━') << L"━┛" << std::endl;

	std::wcout << std::endl;

	// Finds the course with the most grades in our student and returns the amount.
	size_t max_grade_count = 0;
	size_t vec_size = 0;
	for (const auto& pair : student_to_output.getGrades()) {
		vec_size = pair.second.size();
		if (vec_size > max_grade_count) {
			max_grade_count = vec_size;
		}
	}

	// Iterate through all courses in given student and output them.

	std::wcout << L"┏━━━━━━━━┳";

	for (int i = 0; i < max_grade_count + 2; i++) {
		// We choose this specific length because 100.0 and 99.33 can all fit. Any grade to 2 decimal places can fit here with 1 space buffer around it.
		std::wcout << L"━━━━━━━";
		// Check for end character and change shape.
		if (i != max_grade_count + 1) { std::wcout << L'┳'; }
		else { std::wcout << L'┓' << std::endl;; }
	}


	std::wcout << L"┃Courses:┃";
	for (int i = 0; i < max_grade_count; i++) {
		std::wcout << L"Mark " << toUnicodeString(std::to_string(i));

		if (i < 10) {
			std::wcout << L" ┃";
		}
		else {
			std::wcout << L"┃";
		}

	}

	std::wcout << L" Total ┃ Pass? ┃";


	std::wcout << std::endl;

	int grades_counter = 0;
	for (const auto& pair : student_to_output.getGrades()) {
		std::wcout << L"┣━━━━━━━━╋";
		                 
		for (int i = 0; i < max_grade_count + 2; i++) {
			// We choose this specific length because 100.0 and 99.33 can all fit. Any grade to 2 decimal places can fit here with 1 space buffer around it.
			std::wcout << L"━━━━━━━";
			// Check for end character and change shape.
			if (i != max_grade_count + 1) { std::wcout << L'╋'; } else { std::wcout << L'┫' << std::endl;; }
		}
		

		// Print course code.
		std::wcout << L'┃' << toUnicodeString(" " + pair.first + " ");
	
		// Print grades.
		grades_counter = 0;
		std::wcout << L'┃';
		for (const auto& grade : pair.second) {
			grades_counter++;
			std::wcout << L" " << stringRound(grade) << L" ┃";
		}

		for (int i = grades_counter; i < max_grade_count; i++) {
			std::wcout << L"  N/A  ┃";
		}


		// Print out result and total score columns.
		auto map_to_course_ptrs = courses.getCourseMap();
		auto associated_course_result_object = (*map_to_course_ptrs[pair.first]).getGrade(pair.second);

		std::wcout << L" " << stringRound(associated_course_result_object.getScore()) << L" ┃";
		bool result_bool = associated_course_result_object.getResult();

		
		if (result_bool) { // Text colours: Red = 4, Green = 10, White (reset colour) = 15.
			SetConsoleTextAttribute(hConsole, 10);
			std::wcout << L" " << std::boolalpha << result_bool;
			SetConsoleTextAttribute(hConsole, 15);
			std::wcout << L"  ┃";
		} else {
			SetConsoleTextAttribute(hConsole, 4);
			std::wcout << L" " << std::boolalpha << result_bool;
			SetConsoleTextAttribute(hConsole, 15);
			std::wcout << L" ┃";
		}
		
		
		std::wcout << std::endl;
	}

	std::wcout << L"┗━━━━━━━━┻";
	for (int i = 0; i < max_grade_count + 2; i++) {
		// We choose this specific length because 100.0 and 99.33 can all fit. Any grade to 2 decimal places can fit here with 1 space buffer around it.
		std::wcout << L"━━━━━━━";
		// Check for end character and change shape.
		if (i != max_grade_count + 1) { std::wcout << L'┻'; }
		else { std::wcout << L'┛' << std::endl;; }
	}
	std::wcout << std::endl;
	system("pause>0");
}

//void StudentHolder::saveAsJsonFile(Student a_student) {
//
//	a_student.getResults();
//	json a_json_student = a_student;
//	std::map<std::string, double> map;
//	json json_results;
//	for (auto some : a_student.getResults()) {
//		json_results[some.first] = { some.second.getScore(), bool_names(some.second.getResult()) };
//	}
//
//	std::ofstream file("student_results.json");
//	file << a_json_student << "," << json_results;
//}
