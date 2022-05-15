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

int main(int argc, char** argv) {

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
    std::cout << "Marking program written by Connor Colenso, Giovanni Fazio, Avi Goyal and Patrick Mackie" << std::endl << std::endl;

    // Sort vector of students by full name given map is sorted by key by default and we need it alphabetically.
    std::vector<Student> students;
    for (const auto& pair : s.getStudentMap()) {
        students.push_back(pair.second);
    }

    std::sort(students.begin(), students.end(), 
        [](Student& student_1, Student& student_2) -> bool { return student_1.getGivenName() + " " + student_1.getFamilyName() < student_2.getGivenName() + " " + student_2.getFamilyName(); });


    for (const auto& student : students) {
        s.niceOutput(student.identifier, c);
        std::wcout << L"Press any key to continue..." << std::endl << std::endl;
        system("pause>0");
    }

    return 0;
}
