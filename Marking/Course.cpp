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

#include <numeric>
#include <functional>
CourseResult Hybrid::getGrade(std::vector<double> grades) {

	double score_exam = grades[0];
	double score_exam_scaled = grades[0] * weights[0];

	double total_coursework_weight = std::accumulate(weights.begin() + 1, weights.end(), 0.0);
	double score_coursework_scaled = std::inner_product(weights.begin() + 1, weights.end(), grades.begin() + 1, 0.0);
	double score_coursework = score_coursework_scaled / total_coursework_weight;

	bool result = (score_coursework >= 40) && (score_exam >= 40); // Ask James about >= or >.
	double total_score = score_exam_scaled + score_coursework_scaled;

	CourseResult grade(total_score, result);

	return grade;
}

std::vector<double> Hybrid::getWeights() {
	return weights;
}

