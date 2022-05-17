#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"
#include "..\Marking\CourseHolder.h"
#include "..\Marking\StudentHolder.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <string>
#include <codecvt>
#include <locale>
#include <plog/Log.h>

void maximizeWindow() {
    // See https://stackoverflow.com/questions/6606884/setting-console-to-maximized-in-dev-c
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
}

int main(int argc, char** argv) {

    std::cout << "WARNING: If you see no text beyond this point your terminal does not support unicode and cannot run this application. Try CMD on Windows." << std::endl << std::endl;

    maximizeWindow();

    // Magic that allows unicode in console. Code works on uni computers and at home in CMD ONLY, powershell kinda works but doesn't render the tables quite right.
    auto magic_unicode_variable = _setmode(_fileno(stdout), _O_U8TEXT);

    // Setup special colour handling.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CourseHolder c;
	StudentHolder s;

	// This is a bit of a hacky method to support -r but works given getopts is impossible on windows.
	bool resits_only;

	if (argc == 4) {
		c = CourseHolder(argv[argc - 2]);
		s = StudentHolder(argv[argc - 1]);
		if (std::string(argv[1]) == "-r") { 
			resits_only = true;
			std::wcout << "Showing only students requiring resits in alphabetical order as specificed by -r argument." << std::endl << std::endl;
		}
	} else {
		c = CourseHolder(argv[argc - 2]);
		s = StudentHolder(argv[argc- 1]);
		resits_only = false;
		std::wcout << "Showing all students in alphabetical order." << std::endl << std::endl;
	}
	
    std::wcout << L"╔" <<  L"══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════"  << L"╗" << std::endl;
    std::wcout << L"║" << R"(  _    _       _                    _ _                  __   ____  _                _             _                      )" << L"║" << std::endl;
    std::wcout << L"║" << R"( | |  | |     (_)                  (_) |                / _| |  _ \(_)              (_)           | |                     )" << L"║" << std::endl;
    std::wcout << L"║" << R"( | |  | |_ __  ___   _____ _ __ ___ _| |_ _   _    ___ | |_  | |_) |_ _ __ _ __ ___  _ _ __   __ _| |__   __ _ _ __ ___   )" << L"║" << std::endl;
    std::wcout << L"║" << R"( | |  | | '_ \| \ \ / / _ \ '__/ __| | __| | | |  / _ \|  _| |  _ <| | '__| '_ ` _ \| | '_ \ / _` | '_ \ / _` | '_ ` _ \  )" << L"║" << std::endl;
    std::wcout << L"║" << R"( | |__| | | | | |\ V /  __/ |  \__ \ | |_| |_| | | (_) | |   | |_) | | |  | | | | | | | | | | (_| | | | | (_| | | | | | | )" << L"║" << std::endl;
    std::wcout << L"║" << R"(  \____/|_| |_|_| \_/ \___|_|  |___/_|\__|\__, |  \___/|_|   |____/|_|_|  |_| |_| |_|_|_| |_|\__, |_| |_|\__,_|_| |_| |_| )" << L"║" << std::endl;
    std::wcout << L"║" << R"(                                           __/ |                                              __/ |                       )" << L"║" << std::endl;
    std::wcout << L"║" << R"(                                          |___/                                              |___/                        )" << L"║" << std::endl;
    std::wcout << L"║" << R"(                                                                                                                          )" << L"║" << std::endl;
    std::wcout << L"╚" <<  L"══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════"  << L"╝" << std::endl << std::endl;

    std::wcout << "Marking program written by Connor Colenso, Giovanni Fazio, Avi Goyal and Patrick Mackie." << std::endl;
    std::wcout << "This program is best run in cmd, Windows PowerShell will work but does not fully support unicode." << std::endl << std::endl;

    // ---- Sort students vector by full name alphabetically. ----

    std::vector<Student> students;
    for (const auto& pair : s.getStudentMap()) {
        students.push_back(pair.second);
    }

    std::sort(students.begin(), students.end(), 
        [](Student& student_1, Student& student_2) -> bool { return student_1.getGivenName() + " " + student_1.getFamilyName() < student_2.getGivenName() + " " + student_2.getFamilyName(); });

	
	// Load log file.
	plog::init(plog::info, "Log.txt");

	LOG(plog::info) << "Sucessfully loaded a students json with " << students.size() << " students.";
	LOG(plog::info) << "Sucessfully loaded a course json with " << c.getCourseMap().size() << " courses.";

	// ---- Warnings section. ----

	int email_warnings = 0;
	int student_identifier_warnings = 0;
	int student_grades_warnings = 0;

	for (const auto& student : students) {
		
		if (!student.validateEmail().size() != 0) {
			email_warnings += 1;
			LOG(plog::warning) << "Student has an invalid email: " << student.getEmail();
		}
		
		if (!student.validateIdentifier().size() != 0) {
			student_identifier_warnings += 1;
			LOG(plog::warning) << "Student has an invalid identifier: " << student.getIdentifier();
		}

		if (!student.validateGrades()) {
			student_grades_warnings += 1;
			LOG(plog::warning) << "Student " << student.getIdentifier() << " has invalid grades (0 <= grades <= 100).";
		}

	}

	int course_identifier_warnings = 0;
	int course_weights_warnings = 0;

	for (const auto& course_pair : c.getCourseMap()) {
		
		if ((*course_pair.second).validateIdentifer().size() == 0) {
			course_identifier_warnings += 1;
			LOG(plog::warning) << "Course has an invalid identifier: " << (*course_pair.second).getIdentifier();
		}

		if ((*course_pair.second).validateWeights()) {
			course_weights_warnings += 1;
			LOG(plog::warning) << "Course " << (*course_pair.second).getIdentifier() << " has an invalid weight sum. ";
		}

	}

	if (email_warnings + student_identifier_warnings + student_grades_warnings + course_identifier_warnings + course_weights_warnings > 0) {
		
		SetConsoleTextAttribute(hConsole, 12);
		std::wcout << "================================ WARNING ================================" << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
		std::wcout << "Errors in provided files found and listed below. See log.txt for details." << std::endl;

		if (email_warnings > 0) {
			std::wcout << "Invalid Student Emails: " << email_warnings << std::endl;
		}

		if (student_identifier_warnings > 0) {
			std::wcout << "Invalid Student Identifiers: " << student_identifier_warnings << std::endl;
		}

		if (student_grades_warnings > 0) {
			std::wcout << "Invalid Student Grades: " << student_grades_warnings << std::endl;
		}

		if (course_identifier_warnings > 0) {
			std::wcout << "Invalid Course Identifiers: " << course_identifier_warnings << std::endl;
		}

		if (course_weights_warnings > 0) {
			std::wcout << "Invalid Course Weights: " << course_weights_warnings << std::endl;
		}

		SetConsoleTextAttribute(hConsole, 12);
		std::wcout << "================================ WARNING ================================" << std::endl << std::endl;
		SetConsoleTextAttribute(hConsole, 15);
	}


	// ---- Actual table printing. ----

    int student_counter = 0;
    
	if (resits_only) {

		for (auto& student : students) {

			student.populateResults(c);

			if (student.needsResit()) {

				student_counter++;

				s.niceOutput(student.getIdentifier(), c);

				// Change output for last element in vector (end of students json file).
				if (student_counter != students.size()) {
					SetConsoleTextAttribute(hConsole, 10);
					std::wcout << L"Press any key to continue..." << std::endl << std::endl;
				} else {
					SetConsoleTextAttribute(hConsole, 12);
					std::wcout << L"End of students file." << std::endl << std::endl;
				}
				SetConsoleTextAttribute(hConsole, 15);

				// Pauses program until key is entered.
				system("pause>0");
			}
		}
	} else {

		for (auto& student : students) {

			student.populateResults(c);

			student_counter++;

			s.niceOutput(student.getIdentifier(), c);

			// Change output for last element in vector (end of students json file).
			if (student_counter != students.size()) {
				SetConsoleTextAttribute(hConsole, 10);
				std::wcout << L"Press any key to continue..." << std::endl << std::endl;
			} else {
				SetConsoleTextAttribute(hConsole, 12);
				std::wcout << L"End of students file." << std::endl << std::endl;
			}
			SetConsoleTextAttribute(hConsole, 15);

			// Pauses program until key is entered.
			system("pause>0");
		}
	}

    return 0;
}
