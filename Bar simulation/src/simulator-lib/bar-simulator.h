#pragma once

#include <exception>
#include <iostream>
#include <string>

// An exception that is thrown by simulate_bar when it detects an invalid state or data
class incorrect_simulation : public std::runtime_error {
public:
    incorrect_simulation(const std::string& what_arg)
        : runtime_error(what_arg)
    {
        // Nothing to do here        
    }
};

enum Specialty {
    Fraud,
    InternationalSchemes,
    CreativeNihilism,
    SubjectiveResearches,
    FileAnalizis,
    Micromanagement,
    AppliedMaterialization,
    Subjectivistics,
    MagnetismandClearing
};

struct Student {
    unsigned facultyNumber;
    unsigned minutes;
    Specialty spec;
    unsigned enthusiasm;
};


Student readStudent(std::istream& input);

void simulate_bar(std::istream& input, std::ostream& output);
