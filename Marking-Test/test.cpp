#include "gtest/gtest.h"
#include "..\Marking\Course.h"
#include "..\Marking\CourseResult.h"
#include "..\Marking\Student.h"

TEST(Student, StudentConstructor) {
  EXPECT_EQ(1,  1);

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

  Student s("123", "John", "Smith", email, grades, results);

  EXPECT_EQ(s.getEmail(), email);
  EXPECT_EQ(s.getGivenName(), first_name);
  EXPECT_EQ(s.getFamilyName(), last_name);
}

