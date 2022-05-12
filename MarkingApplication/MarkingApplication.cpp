#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"
#include "..\Marking\Course.cpp"
#include "..\Marking\CourseResult.cpp"
#include "..\Marking\Student.cpp"
#include <iostream>

int main() {
    std::map<std::string, std::vector<double>> grades = { {"MATH1", {1,2,3,4} }, {"MATH2", {1,2,3,4} } };
    CourseResult test(60.0, true);
    std::map<std::string, CourseResult> results = { {"MATH1", CourseResult(60, true)}, {"MATH2", CourseResult(80, true)} };
    std::cout << std::boolalpha << test.getResult() << std::endl;
    std::cout << test.getScore() << std::endl;

    Student test_1("YY12345678", "Jack", "Smith", "Jack@gmail.com", grades, results);
    std::cout << test_1.getEmail() << std::endl;

}
