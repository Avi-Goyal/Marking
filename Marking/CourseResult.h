#pragma once

class CourseResult {
	double score{};
	bool result{};
public:
	CourseResult(double tmp_score, bool result);
	double getScore();
	bool getResult();

};
