#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <numeric>

// This is the abstract base class, therefore it has no constructor.
class Course {
    std::string identifier;
    std::vector<double> weights;

    virtual double getGrade();
};

// Callable classes.
class ExamOnly : Course {
    ExamOnly(std::string identifier, std::vector<double> weights);
    //double getGrade();
};

class CourseworkOnly : Course {
    CourseworkOnly();
};

class Hybrid : Course {
    Hybrid();
};
