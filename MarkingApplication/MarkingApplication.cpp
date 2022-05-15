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
    StudentHolder s(R"(../Test Data - DO NOT EDIT/large_students.json)");
    CourseHolder  c(R"(../Test Data - DO NOT EDIT/large_courses.json)");

    for (const auto& pair : s.getStudentMap()) {
        s.niceOutput(pair.second.identifier, c);
    }

    return 0;
}
