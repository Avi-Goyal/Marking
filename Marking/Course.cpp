#include <windows.h>
#include "Course.h"

CourseResult ExamOnly::getGrade(std::vector<double> grades) {
	double score = grades[0] * weights[0];
	bool result = (score < 40 ? 0 : 1);

	CourseResult grade(score, result);

	return grade;
}

std::vector<double> ExamOnly::getWeights() {
	return weights;
}

CourseResult CourseworkOnly::getGrade(std::vector<double> grades) {
	double score = std::inner_product(weights.begin(), weights.end(), grades.begin(), 0.0);
	bool result = (score < 40 ? 0 : 1);

	CourseResult grade(score, result);

	return grade;
}

std::vector<double> CourseworkOnly::getWeights() {
	return weights;
}

CourseResult Hybrid::getGrade(std::vector<double> grades) {
	double score = std::inner_product(weights.begin(), weights.end(), grades.begin(), 0.0);
	bool result = (score < 40 || grades[0] < 40 ? 0 : 1);

	CourseResult grade(score, result);

	return grade;
}

std::vector<double> Hybrid::getWeights() {
	return weights;
}

