#include <windows.h>
#include "Course.h"

const std::vector<double> Course::getWeights() const  {
	return weights;
}
	
const Credits Course::getNumberOfCredits() const {
	return numberOfCredits;
}

const std::string Course::getIdentifier() const {
	return identifier;
}

const std::smatch Course::validateIdentifer() const {

	std::regex regular_expression("^([A-Z]{3})([0-9]{3})$");
	std::smatch match;

	if (!std::regex_search(identifier, match, regular_expression)) {} // REMOVE ME!!!!!!!!!!!

	return match;

}

const bool Course::validateWeights() const {

	double sum_weights = std::accumulate(weights.begin(), weights.end(), 0.0);

	if ((1 - 1e-8 < sum_weights) && (sum_weights > 1 + 1e-8)) {
		return true;
	}

	return false;

}

const CourseResult ExamOnly::getGrade(const std::vector<double>& grades) const {

	const double score = grades[0] * weights[0];
	const bool result = (score >= 40 ? true : false);

	const CourseResult grade(score, result);

	return grade;
}

const CourseResult CourseworkOnly::getGrade(const std::vector<double>& grades) const {

	const double score = std::inner_product(weights.begin(), weights.end(), grades.begin(), 0.0);
	const bool result = (score >= 40 ? true : false);

	const CourseResult grade(score, result);

	return grade;
}

const CourseResult Hybrid::getGrade(const std::vector<double>& grades) const {

	const double score_exam = grades[0];
	const double score_exam_scaled = grades[0] * weights[0];

	const double total_coursework_weight = std::accumulate(weights.begin() + 1, weights.end(), 0.0);
	const double score_coursework_scaled = std::inner_product(weights.begin() + 1, weights.end(), grades.begin() + 1, 0.0);
	const double score_coursework = score_coursework_scaled / total_coursework_weight;

	const bool result = (score_coursework >= 40) && (score_exam >= 40);
	const double total_score = score_exam_scaled + score_coursework_scaled;

	const CourseResult grade(total_score, result);

	return grade;
}
