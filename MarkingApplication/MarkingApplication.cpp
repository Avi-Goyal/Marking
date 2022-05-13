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


	CourseHolder c("/Users/GoRi1/Desktop/course.json");
	StudentHolder s("/Users/GoRi1/Desktop/nest.json");

	Student a_student = s.getStudent("JS12345678");
	a_student.populateResults(c);

	for (auto pairs : a_student.getResults()) {
		std::cout << pairs.first << std::endl;
		std::cout << std::boolalpha << pairs.second.getResult() << std::endl;
	}



	return 0;
}
