#include "Course.h"

double Course::getGrade() { return 1.0; }


ExamOnly::ExamOnly(std::string identifier, std::vector<double> weights) {
    double sum_of_weights = std::accumulate(weights.begin(), weights.end(), 0.0);
    if (sum_of_weights != 1.0) { std::cout << "ERROR: Weights invalid." << std::endl; }
};
