#include "Course.h"

double ExamOnly::getGrade(std::vector<double> grades) {
	return std::inner_product(weights.begin(), weights.end(), grades.begin(), 0.0);
}

std::vector<double> ExamOnly::getWeights() {
	return weights;
}

double CourseworkOnly::getGrade(std::vector<double> grades) {
	return std::inner_product(weights.begin(), weights.end(), grades.begin(), 0.0);
}

std::vector<double> CourseworkOnly::getWeights() {
	return weights;
}

double Hybrid::getGrade(std::vector<double> grades) {
	return std::inner_product(weights.begin(), weights.end(), grades.begin(), 0.0);
}
std::vector<double> Hybrid::getWeights() {
	return weights;
}
