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

	std::regex regular_expression_0("^([A-Z]{2})([0-9]{8})$");
	std::smatch match_0;
	std::string id = "AA12345678";
	std::regex_search(id, match_0, regular_expression_0);

	std::regex regular_expression_1("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	std::smatch match_1;
	std::string email = "user@gmail.com";
	std::regex_search(email, match_1, regular_expression_1);

	return 0;
}
