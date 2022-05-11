#include "CourseResult.h"

// constructor for object CourseResult
CourseResult::CourseResult(double tmp_score, bool result) : result(result) {

	if ((tmp_score >= 0) && (tmp_score <= 100)) {
		score = tmp_score;
	}

}
