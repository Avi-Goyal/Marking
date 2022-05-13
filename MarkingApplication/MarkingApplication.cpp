#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"
#include "..\Marking\Holder.h"

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

#include<regex>


	StudentHolder s("/Users/GoRi1/Desktop/nest.json");
	Student st = s.getStudent("JS12345678");

	std::vector<double> course_grades{};
	st.getCourseGrades("AMF126", &course_grades);

	print_vector(course_grades);






	return 0;
}
