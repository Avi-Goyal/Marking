#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"

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
	CourseHolder s(R"(../small_courses.json)");
	return 0;
}
