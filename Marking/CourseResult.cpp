#include "CourseResult.h"

// constructor for object CourseResult
CourseResult::CourseResult(const double& tmp_score, const bool& result) : result(result) {
	if ((tmp_score >= 0) && (tmp_score <= 100)) {
		score = tmp_score;
	}
}

const bool CourseResult::getResult() const {
	return result;
}

const double CourseResult::getScore() const {
	return score;
}
