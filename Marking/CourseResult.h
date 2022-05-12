#pragma once

class CourseResult {

	double score{};
	bool result{};

public:
	CourseResult(double tmp_score, bool result);

	double getScore();
	bool getResult();

};

// This should be in CourseResult.cpp but program refuses to build if it's there - no idea why currently.
CourseResult::CourseResult(double tmp_score, bool result) : result(result) {
	if ((tmp_score >= 0) && (tmp_score <= 100)) {
		score = tmp_score;
	}
}


bool CourseResult::getResult() {
	return result;
}

double CourseResult::getScore() {
	return score;
}

