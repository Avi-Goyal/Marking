#pragma once

const class CourseResult {
private:
	double score;
	bool result;
public:
	CourseResult(const double& tmp_score, const bool& result);

	const double getScore() const;
	const bool getResult() const;
};
