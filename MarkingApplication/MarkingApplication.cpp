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

    // Run this to see example of pretty printing.

    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //// you can loop k higher to see more color choices
    //for (int k = 1; k < 255; k++)
    //{
    //    // pick the colorattribute k you want
    //    SetConsoleTextAttribute(hConsole, k);
    //    std::cout << k << " I want to be nice today!" << std::endl;
    //}

    CourseHolder  c(R"(../Test Data - DO NOT EDIT/large_courses.json)");
    StudentHolder s(R"(../Test Data - DO NOT EDIT/large_students.json)");

    for (const auto& pair : s.getStudentMap()) {
        s.niceOutput(pair.second.identifier, c);
    }

    return 0;
}
