#include "CourseResult.h"
#include <plog/Log.h>

// constructor for object CourseResult
CourseResult::CourseResult(const double& tmp_score, const bool& result) : result(result) {
	
	// Tiny bit of room for floating point errors.
	if ((tmp_score >= 0 - 1e-8) && (tmp_score <= 100 + 1e-8)) {
		score = tmp_score;
	} else {
		plog::init(plog::info, "Log.txt");
		LOG(plog::fatal) << "Score provided to CourseResult constructor for is out of range. Score provided was " + std::to_string(tmp_score) + ".";
		throw std::invalid_argument("Score provided to CourseResult constructor is out of range. See log for details.");
	}
}

const bool CourseResult::getResult() const {
	return result;
}

const double CourseResult::getScore() const {
	return score;
}
