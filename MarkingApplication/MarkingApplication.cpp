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

	//StudentHolder s(R"(../small_students.json)");
	//CourseHolder g(R"(../small_courses.json)");
	//Course* sth = g.getCourse("AMF123");
	//std::cout<< sth->getGrade(s.getGrades("JS12345678", "AMF123"));

	/*CourseHolder s(R"(../small_courses.json)");

	std::vector<double> AMF_weights = { 0.2, 0.2, 0.1, 0.5 };
	ExamOnly* course_0 = s.getCourse("AMF123");

	ExamOnly exam_course = course_0;


	*/

	return 0;
}
