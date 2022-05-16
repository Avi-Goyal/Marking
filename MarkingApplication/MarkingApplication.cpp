#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"
#include "..\Marking\CourseHolder.h"
#include "..\Marking\StudentHolder.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <string>
#include <codecvt>
#include <locale>


void maximizeWindow() {
    // See https://stackoverflow.com/questions/6606884/setting-console-to-maximized-in-dev-c
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
}

//int main(int argc, char** argv) { std::cout << "Test" << std::endl; }

int main(int argc, char** argv) {

    maximizeWindow();

    // Setup special colour handling.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CourseHolder  c(R"(../Test Data - DO NOT EDIT/large_courses.json)");
    StudentHolder s(R"(../Test Data - DO NOT EDIT/large_students.json)");

    std::cout << R"(  _    _       _                    _ _                  __   ____  _                _             _                     )" << std::endl;
    std::cout << R"( | |  | |     (_)                  (_) |                / _| |  _ \(_)              (_)           | |                    )" << std::endl;
    std::cout << R"( | |  | |_ __  ___   _____ _ __ ___ _| |_ _   _    ___ | |_  | |_) |_ _ __ _ __ ___  _ _ __   __ _| |__   __ _ _ __ ___  )" << std::endl;
    std::cout << R"( | |  | | '_ \| \ \ / / _ \ '__/ __| | __| | | |  / _ \|  _| |  _ <| | '__| '_ ` _ \| | '_ \ / _` | '_ \ / _` | '_ ` _ \ )" << std::endl;
    std::cout << R"( | |__| | | | | |\ V /  __/ |  \__ \ | |_| |_| | | (_) | |   | |_) | | |  | | | | | | | | | | (_| | | | | (_| | | | | | |)" << std::endl;
    std::cout << R"(  \____/|_| |_|_| \_/ \___|_|  |___/_|\__|\__, |  \___/|_|   |____/|_|_|  |_| |_| |_|_|_| |_|\__, |_| |_|\__,_|_| |_| |_|)" << std::endl;
    std::cout << R"(                                           __/ |                                              __/ |                      )" << std::endl;
    std::cout << R"(                                          |___/                                              |___/                       )" << std::endl;
    std::cout << std::endl;
    std::cout << "Marking program written by Connor Colenso, Giovanni Fazio, Avi Goyal and Patrick Mackie." << std::endl;
    std::cout << "This program is best run in cmd, Windows PowerShell will work but does not fully support unicode." << std::endl << std::endl;

    // ---- Sort students vector by full name alphabetically. ----

    std::vector<Student> students;
    for (const auto& pair : s.getStudentMap()) {
        students.push_back(pair.second);
    }

    std::sort(students.begin(), students.end(), 
        [](Student& student_1, Student& student_2) -> bool { return student_1.getGivenName() + " " + student_1.getFamilyName() < student_2.getGivenName() + " " + student_2.getFamilyName(); });

    // -----------------------------------------------------------

    int student_counter = 0;
    for (const auto& student : students) {
        student_counter++;

        s.niceOutput(student.getIdentifier(), c);

        // Change output for last element in vector (end of students json file).
        if (student_counter != students.size()) {
            SetConsoleTextAttribute(hConsole, 10);
            std::wcout << L"Press any key to continue..." << std::endl << std::endl;
        }
        else {
            SetConsoleTextAttribute(hConsole, 12);
            std::wcout << L"End of students file." << std::endl << std::endl;
        }
        SetConsoleTextAttribute(hConsole, 15);

        // Pauses program until key is entered.
        system("pause>0");
    }

    return 0;
}
