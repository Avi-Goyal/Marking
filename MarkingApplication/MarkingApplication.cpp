#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"
#include "..\Marking\CourseHolder.h"
#include "..\Marking\StudentHolder.h"

void print_vector(std::vector<double> const& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
}

void print_map(std::map<std::string, std::vector<double>> const& m)
{
	for (auto const& pair : m) {
		std::cout << "{" << pair.first << ": "; print_vector(pair.second); std::cout << "}" << std::endl;
	}
}


int main() {

	// !!! 7 WARNINGS TO DEAL WITH !!! \\

	// SPECIFICALLY FOR CONNOR: WE HAVE TO ASK JAMES HOW DO CREDITS APPEAR IN THE JSON FILE, AS HE WANTS US TO USE AN ENUM EXACTELY LIKE THE FOLLOWING:
	enum numberOfCredits {TenCredits, TwentyCredits};
	// BUT I AM NOT SURE WHY, WE MIGHT HAVE TO INTEGRATE ANOTHER SWITCH STATEMENT AS YOU DID FOR courseType.

	// To do: 
	// FIGURE OUT HOW TO USE GETOPT() FOR MARKING APPLICATION (ARGC, ARGV, FLAGS ETC.).
	// HOW DOES JAMES WANT THE USER TO INETRACT WITH THE APP? SHOULD THE USER HAVE OPTIONS TO CHOOSE WHAT STUDENT TO DISPLAY? (LIKE A MENU OR STH).
	

	// IMPLEMENTATION TO REPORT THE RESULTS OF A SINGLE STUDENT (FURTHER DOWN I ALSO IMPLEMENT A METHOD TO REPORT ALL STUDENTS' RESULTS):
	CourseHolder c("/Users/GoRi1/Desktop/course.json");
	StudentHolder s("/Users/GoRi1/Desktop/nest.json");

	Student a_student = s.getStudent("JS12345678");
	a_student.populateResults(c);


	// SHOULD THE APP ONLY DISPLAY A STUDENT (ALONG WITH HIS RESULTS) CHOSEN BY THE USER? :
	//s.niceOutput("JS12345678", c);

	// OR SHOULD THE APP JUST DISPLAY AT ONCE ALL STUDENTS INFORMATION AT THE TOP AND ALL THE RESULTS AT THE BOTTOM?
	// WE COULD TO THIS BY REARRANGING THE niceOutput FUNCTION IN THIS WAY.
	for (auto students : s.getStudentMap()) {
		students.second.populateResults(c);
		s.niceOutput(students.first, c);
	}
	// OR SHOULD WE DISPLAY THE STUDENTS ON THE LEFT AND THE RESULTS ON THE RIGHT?
	// AND TO DO THIS, DO WE NEED SOME SEPCIAL LIBRARY<>?


	// SHOULD THE APP OFFER TO SAVE THE RESULTS FOR A SPECIFIC STUDENT?
	s.saveAsJsonFile(a_student);
	// OR SAVE ALL STUDENTS AND RESULTS? (AGAIN USING A FOR RANGE LOOP SIMILAR TO THE ABOVE).

	return 0;
}
