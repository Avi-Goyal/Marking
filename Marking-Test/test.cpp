#include "gtest/gtest.h"
#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"
#include "..\Marking\Holder.h"
#include <vector>

TEST(Student, StudentConstructor) {

	std::string identifier = "AA12345678";
	std::string email = "js@gmail.com";
	std::string first_name = "John";
	std::string last_name = "Smith";

	std::string amf = "AMF123", nla = "NLA123";

	std::vector<double> grades_amf = { 50, 40, 70 };
	std::vector<double> grades_nla = { 35, 80, 100 };

	std::map<std::string, std::vector<double>> grades;

	grades.insert({ amf, grades_amf });
	grades.insert({ nla, grades_nla });

	std::map<std::string, CourseResult> results{};

	Student s(identifier, first_name, last_name, email, grades, results);

	EXPECT_EQ(s.getIdentifier(), identifier);
	EXPECT_EQ(s.getEmail(), email);
	EXPECT_EQ(s.getGivenName(), first_name);
	EXPECT_EQ(s.getFamilyName(), last_name);
}

TEST(StudentHolder, Constructor_From_Filepath_Small_Students_JSON) {
	StudentHolder s(R"(../small_students.json)");

	Student student_0 = s.getStudent("JS12345678");
	Student student_1 = s.getStudent("GF12345678");

	std::vector<double>student_0_AMF_grades = { 75, 50, 65, 40 };
	std::vector<double>student_0_NLA_grades = { 70, 35, 50, 50 };
	std::vector<double>student_0_PDE_grades = { 80, 20, 35, 80 };

	std::vector<double>student_1_AMF_grades = { 30, 55, 65, 70 };
	std::vector<double>student_1_NLA_grades = { 80, 75, 50, 50 };
	std::vector<double>student_1_PDE_grades = { 50, 50, 35, 80 };

	EXPECT_EQ(student_0.getEmail(), "js123@gmail.org");
	EXPECT_EQ(student_0.getFamilyName(), "Smith");
	EXPECT_EQ(student_0.getGivenName(), "John");
	EXPECT_EQ(student_0.getIdentifier(), "JS12345678");
	EXPECT_EQ(student_0.getGrades()["AMF123"], student_0_AMF_grades);
	EXPECT_EQ(student_0.getGrades()["NLA123"], student_0_NLA_grades);
	EXPECT_EQ(student_0.getGrades()["PDE123"], student_0_PDE_grades);

	EXPECT_EQ(student_1.getEmail(), "gf123@gmail.com");
	EXPECT_EQ(student_1.getFamilyName(), "Fazio");
	EXPECT_EQ(student_1.getGivenName(), "Gio");
	EXPECT_EQ(student_1.getIdentifier(), "GF12345678");
	EXPECT_EQ(student_1.getGrades()["AMF123"], student_1_AMF_grades);
	EXPECT_EQ(student_1.getGrades()["NLA123"], student_1_NLA_grades);
	EXPECT_EQ(student_1.getGrades()["PDE123"], student_1_PDE_grades);
}

TEST(CourseHolder, Constructor_From_Filepath_Small_Courses_JSON) {
	CourseHolder s(R"(../small_courses.json)");
	
	std::vector<double> AMF_weights = { 0.2, 0.2, 0.1, 0.5 };
	EXPECT_EQ((*s.getCourse("AMF123")).getWeights(), AMF_weights);

	std::vector<double> NLA_weights = { 0.02, 0.02, 0.03, 0.94 };
	//EXPECT_EQ((*s.getCourse("NLA123")).getWeights(), NLA_weights);
	//EXPECT_EQ(typeid((*s.getCourse("NLA123"))).name(), "CourseworkOnly");

	std::vector<double> PDE_weights = { 0.05, 0.05, 0.05, 0.85 };
	//EXPECT_EQ((*s.getCourse("PDE123")).getWeights(), PDE_weights);
	//EXPECT_EQ(typeid((*s.getCourse("PDE123"))).name(), "Hybrid");
}