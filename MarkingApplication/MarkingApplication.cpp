#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"
#include "..\Marking\CourseHolder.h"
#include "..\Marking\StudentHolder.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include<iomanip>
#include<string>
#include<cstdlib>

#include <string>
#include <codecvt>
#include <locale>


using convert_t = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_t, wchar_t> strconverter;
std::wstring to_wstring(std::string str) {
    return strconverter.from_bytes(str);
}

void operator<<(std::wostream& ostream, std::string str) {
    ostream << to_wstring(str);
}


int main(int argc, char** argv) {
    std::set<std::string> arguments_vector;

    _setmode(_fileno(stdout), _O_U16TEXT);



    /*for (int i = 1; i < argc; i++) {
        arguments_vector.insert(argv[i]);
    }

    if (arguments_vector.count("-r")) {
        std::cout << "Found r!" << std::endl;
    }
    else {
        std::cout << "Did not find r!" << std::endl;
    }*/
    
   /* CourseHolder c(argv[1]);
    StudentHolder s(argv[2]);*/


    

    std::string name = "John";

    std::wcout << L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
    std::wcout << L"┃               Name                        ┃" << name;
    //std::wcout << L"┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << std::endl;
    //std::wcout << L"┃                                           ┃" << std::endl;
    //std::wcout << L"┃                                           ┃" << std::endl;
    //std::wcout << L"┃                                           ┃" << std::endl;


    //for (auto students : s.getStudentMap()) {
    //    students.second.populateResults(c);
    //    s.niceOutput(students.first, c);
    //}
    //

    //std::cout << argv[1] << std::endl;
    //std::cout << argv[2] << std::endl;
    //std::cout << argv[3] << std::endl;
    //std::/*string a;
    //std::cin >> a;*/

    return 0;
}
