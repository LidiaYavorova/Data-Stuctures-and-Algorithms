#pragma once
#include <exception>
#include <vector>
#include <fstream>
#include <stack>
#include <iostream>

// An exception that is thrown by evaluate when it detects an incorrect expression
class incorrect_expression : public std::invalid_argument {
public:
    incorrect_expression(const std::string& what_arg)
        : invalid_argument(what_arg)
    {
        // Nothing to do here        
    }
};
struct Ops {
    char name;
    char operation;
    int priority;
    char association;
};

unsigned linesCount(std::istream& ops);

bool isOperation(const std::vector<Ops>& vectorOfOps, char ch);

Ops getOp(const std::vector<Ops>& vectorOfOps, const char ch);

double applyOperation(char operation, double leftOperand, double rightOperand);

void calculate(const std::vector<Ops>& arrayOfOps, std::stack<double>& nums, std::stack<char>& operators);

double evaluate(const char* expression, std::istream& ops);