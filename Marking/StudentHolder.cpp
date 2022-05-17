#include "StudentHolder.h"
#include "Student.h"

StudentHolder::StudentHolder() {}

// ----------------- Utility functions to facilitate niceOutput -----------------

// Helper function to print table.
void printMid(int number_of_sections, std::wstring start_char, std::wstring mid_char, std::wstring end_char) {
	std::wcout << start_char << L"━━━━━━━━" << mid_char;
	for (int i = 0; i < number_of_sections; i++) {
		// We choose this specific length because any grade to 2 decimal places can fit here with 1 space buffer around it.
		std::wcout << L"━━━━━━━";
		// Check for end character and change shape.
		if (i != number_of_sections -1 ) { std::wcout << mid_char; }
		else { std::wcout << end_char << std::endl;; }
	}
}

// Magic.
std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> strconverter;
const std::wstring toUnicodeString(std::string str) {
	return strconverter.from_bytes(str);
}

const std::wstring stringRound(double grade) {
	double rounded_grade = round(grade);
	std::string rounded_string_grade = std::to_string(grade);

	if (rounded_string_grade.size() > 5) {
		std::string tmp = rounded_string_grade.substr(0, 5);
		return toUnicodeString(tmp);
	}

	return toUnicodeString(rounded_string_grade);
}

// -----------------------------------------------------------------------------

StudentHolder::StudentHolder(const std::string& file_path_name) {
	
	std::ifstream json_file(file_path_name);
	students = nlohmann::json::parse(json_file);

	for (const auto& student : students) {
		map_id_to_student[student.getIdentifier()] = student;
	}
}

const Student StudentHolder::getStudent(const std::string& student_id) const {
	return map_id_to_student.at(student_id);
}

const std::vector<double> StudentHolder::getGrades(const std::string& student_id, const std::string& course_id) const {
	return map_id_to_student.at(student_id).getGrades().at(course_id);
}

const std::map<std::string, Student> StudentHolder::getStudentMap() const {
	return map_id_to_student;
}

void StudentHolder::niceOutput(const std::string& student_id, const CourseHolder& courses) const {
	
	// Very long complex function but hopefully it makes sense with the comments.

	bool needs_resits = false;
	std::vector<double> all_marks;

	// Setup special colour handling.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Used twice later.
	auto map_to_course_ptrs = courses.getCourseMap();

	// ---------------------------------- Print out basic information ---------------------------------------------
	Student student_to_output = map_id_to_student.at(student_id);

	std::wstring wstring_full_name = toUnicodeString(student_to_output.getFullName());
	std::wstring wstring_identifier = toUnicodeString(student_to_output.getIdentifier());
	std::wstring wstring_email = toUnicodeString(student_to_output.getEmail());

	std::vector<size_t> vector_of_strings = { wstring_identifier.size(), wstring_full_name.size(), wstring_email.size() };
	size_t max_size_string = *std::max_element(vector_of_strings.begin(), vector_of_strings.end());

	std::wcout << L"┏━━━━━━━━━━━━┳━" << std::wstring(max_size_string, L'━') << L"━┓" << std::endl;
	std::wcout << L"┃ Student ID ┃ " << wstring_identifier << std::wstring(1 + max_size_string - wstring_identifier.size(), ' ') << L"┃" << std::endl;
	std::wcout << L"┣━━━━━━━━━━━━╋━" << std::wstring(max_size_string, L'━') << L"━┫" << std::endl;
	std::wcout << L"┃ Full Name  ┃ " << wstring_full_name << std::wstring(1 + max_size_string - wstring_full_name.size(), ' ') << L"┃" << std::endl;
	std::wcout << L"┣━━━━━━━━━━━━╋━" << std::wstring(max_size_string, L'━') << L"━┫" << std::endl;
	std::wcout << L"┃ Email      ┃ " << wstring_email << std::wstring(1 + max_size_string - wstring_email.size(), ' ') << L"┃" << std::endl;
	std::wcout << L"┗━━━━━━━━━━━━┻━" << std::wstring(max_size_string, L'━') << L"━┛" << std::endl << std::endl;

	// ------------------------------------------------------------------------------------------------------------

	// Finds the course with the most grades in our student. This is necessary to determine how long to make the table.
	size_t max_grade_count = 0;
	size_t vec_size = 0;
	for (const auto& pair : student_to_output.getGrades()) {
		vec_size = pair.second.size();
		if (vec_size > max_grade_count) {
			max_grade_count = vec_size;
		}
	}

	// Add 3 because grades + course name + aggregate mark + credits + pass/fail.
	const int total_grade_table_length = (int) max_grade_count + 3; 
	
	printMid(total_grade_table_length, L"┏", L"┳", L"┓");

	// ---------------------------------- Print out the column headers for student grades, total and pass. ------------------------

	std::wcout << L"┃Courses:┃";
	for (int i = 0; i < max_grade_count; i++) {
		std::wcout << L"Mark " << toUnicodeString(std::to_string(i));

		// Mark 0 vs Mark10 needs 1 less space because there is not enough room otherwise.
		if (i < 10) {
			std::wcout << L" ┃";
		}
		else {
			std::wcout << L"┃";
		}

	}

	std::wcout << L" Total ┃Credits┃ Pass? ┃" << std::endl;

	// ---------------------------------- Print actual grades, total and pass/fail to each row ----------------------------------

	int grades_counter = 0;
	for (const auto& pair : student_to_output.getGrades()) {

		printMid(total_grade_table_length, L"┣", L"╋", L"┫");

		// Print course code.
		std::wcout << L'┃' << toUnicodeString(" " + pair.first + " ");
	
		// Print grades.
		grades_counter = 0;
		std::wcout << L'┃';
		for (const auto& grade : pair.second) {
			grades_counter++;
			std::wcout << L" " << stringRound(grade) << L" ┃";
		}

		// Print N/A for remainder of grades to fill in table.
		for (int i = grades_counter; i < max_grade_count; i++) {
			// Text colours: Grey = 8, White (reset colour) = 15.
			SetConsoleTextAttribute(hConsole, 8);
			std::wcout << L"  N/A  ";
			SetConsoleTextAttribute(hConsole, 15);
			std::wcout << L'┃';
		}

		// Print out result and total score.
		auto associated_course_result_object = (*map_to_course_ptrs[pair.first]).getGrade(pair.second);

		std::wcout << L" " << stringRound(associated_course_result_object.getScore()) << L" ┃";
		std::wcout << L" " << (*map_to_course_ptrs[pair.first]).getNumberOfCredits() << L"    ┃";

		// Used in extra misc information table.
		all_marks.push_back(associated_course_result_object.getScore());
		bool result_bool = associated_course_result_object.getResult();

		// True and false take different amounts of space and have differnet colours.
		if (result_bool) { 
			// Text colours: Red = 4, Green = 10, White (reset colour) = 15.
			SetConsoleTextAttribute(hConsole, 10);
			std::wcout << L" " << std::boolalpha << result_bool;
			SetConsoleTextAttribute(hConsole, 15);
			std::wcout << L"  ┃";
		} else {
			// If ever false we need resits so this makes the misc information later on easier to parse.
			needs_resits = true;
			SetConsoleTextAttribute(hConsole, 4);
			std::wcout << L" " << std::boolalpha << result_bool;
			SetConsoleTextAttribute(hConsole, 15);
			std::wcout << L" ┃";
		}
		
		std::wcout << std::endl;
	}

	printMid(total_grade_table_length, L"┗", L"┻", L"┛");

	// ---------------------------------- Print extra misc information, pass/fail, aggregate mark, total credits

	// Necessary so we can weight marks properly.
	std::vector<int> credit_vector;
	int total_credits = 0;
	int credits;
	
	// Get total credits.
	for (const auto& pair : student_to_output.getGrades()) {
		credits = (*map_to_course_ptrs[pair.first]).getNumberOfCredits();
		total_credits += credits;
		credit_vector.push_back(credits);
	}

	/// To find aggregate mark we have to weight our results by their credits.
	/// I.e. credits [20, 10, 10, 20, 20] have weights [0.25, 0.125, 0.125, 0.25, 0.25]
	/// and from here can be dot producted with course aggregate marks for overall aggregate mark. 
	std::vector<double> credits_vector_weights;
	double sum_credits = std::accumulate(credit_vector.begin(), credit_vector.end(), 0);
	for (const auto& credits : credit_vector) {
		credits_vector_weights.push_back(credits / sum_credits);
	}

	double aggregate_mark = std::inner_product(all_marks.begin(), all_marks.end(), credits_vector_weights.begin(), 0.0);
	std::wstring aggregate_mark_string = stringRound(aggregate_mark);

	std::wcout << std::endl;
	std::wcout << L"┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━┓" << std::endl;
	std::wcout << L"┃ Total Credits        ┃ " << total_credits << ((total_credits < 100) ? L"     " : L"    ") << L"┃" << std::endl;
	std::wcout << L"┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━┫" << std::endl;
	std::wcout << L"┃ Needs Resit(s)       ┃ ";
	if (needs_resits) {
		// Text colours: Red = 4, Green = 10, White (reset colour) = 15.
		SetConsoleTextAttribute(hConsole, 10);
		std::wcout << std::boolalpha << needs_resits;
		SetConsoleTextAttribute(hConsole, 15);
		std::wcout << L"   ┃";
	} else {
		SetConsoleTextAttribute(hConsole, 4);
		std::wcout << std::boolalpha << needs_resits;
		SetConsoleTextAttribute(hConsole, 15);
		std::wcout << L"  ┃";
	}

	std::wcout << std::endl;

	std::wcout << L"┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━┫" << std::endl;
	std::wcout << L"┃ Aggregate Mark       ┃ " << aggregate_mark_string << L"  ┃" << std::endl;
	std::wcout << L"┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━┫" << std::endl;
	std::wcout << L"┃ Degree Classiciation ┃";
	if (aggregate_mark < 40) {
		std::wcout << L" FAIL   ┃";
	} else if (aggregate_mark < 50) {
		std::wcout << L" Third  ┃";
	} else if (aggregate_mark < 60) {
		std::wcout << L" 2:2    ┃";
	} else if (aggregate_mark < 70) {
		std::wcout << L" 2:1    ┃";
	} else {
		std::wcout << L" 1:1    ┃";
	}
	std::wcout << std::endl << L"┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━┛" << std::endl;

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
