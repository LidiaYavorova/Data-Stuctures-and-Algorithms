#include "expression.h"
#include "verifyingFunctions.inl"

unsigned linesCount(std::istream& ops)
{
    size_t currentPosition = ops.tellg();
    ops.seekg(0, std::ios::beg);
    unsigned count = 1;
    while (true)
    {
        char current = ops.get();
        if (ops.eof())
        {
            break;
        }
        if (current == '\n')
        {
            count++;
        }
    }
    ops.clear();
    ops.seekg(currentPosition);
    return count;
}

bool isOperation(const std::vector<Ops>& vectorOfOps, char ch)
{
    for (size_t i = 0; i < vectorOfOps.size(); i++)
    {
        if (ch == vectorOfOps[i].name)
        {
            return true;
        }
    }
    return false;
}

Ops getOp(const std::vector<Ops>& vectorOfOps, const char ch)
{
    for (size_t i = 0; i < vectorOfOps.size(); i++)
    {
        if (ch == vectorOfOps[i].name)
        {
            return vectorOfOps[i];
        }
    }
    throw incorrect_expression("Invalid operation");
}

double applyOperation(char operation, double leftOperand, double rightOperand)
{
    switch (operation) {
    case '+':
        return leftOperand + rightOperand;
        break;
    case '-':
        return leftOperand - rightOperand;
        break;
    case '*':
        return leftOperand * rightOperand;
        break;
    }
    return leftOperand / rightOperand;
}

void calculate(std::vector<Ops>& arrayOfOps, std::stack<double>& nums, char ch)
{
    double rightOperand = nums.top(); nums.pop();
    double leftOperand = nums.top(); nums.pop();
    char operation = getOp(arrayOfOps, ch).operation;
    double result = applyOperation(operation, leftOperand, rightOperand);
    nums.push(result);

}

double evaluate(const char* expression, std::istream& ops)
{
    isNullPtrExpression(expression);
    if (isEmptyExpression(expression))
    {
        return 0.0;
    }
    verifyFirstAndLastCharacter(expression);

    unsigned countOfOps = linesCount(ops);
    std::vector<Ops> vectorOfOps(countOfOps);
    for (size_t i = 0; i < vectorOfOps.size(); i++)
    {
        ops >> vectorOfOps[i].name >> vectorOfOps[i].operation >> vectorOfOps[i].priority >> vectorOfOps[i].association;
    }
    Ops brackets = { '(','(',-1,'L' };
    vectorOfOps.push_back(brackets);
    verifyIntervalsOperationsOrderAndBracketsInExpression(expression, vectorOfOps);

    std::stack<double> numbers;
    std::stack<char> operations;
    bool unary = false;
    int number = 0;
    for (size_t i = 0; i < strlen(expression); i++)
    {
        number = 0;
        if (expression[i] == ' ') {
            continue;
        }
        else if (isNumber(expression[i]))
        {
            while (isNumber(expression[i]))
            {
                number = number * 10 + expression[i] - '0';
                ++i;
            }
            --i;
            if (unary)
            {
                numbers.push(-number);
                unary = false;
            }
            else
            {
                numbers.push(number);
            }
        }
        else if (expression[i] == '-')
        {
            unary = true;
        }
        else if (expression[i] == '(')
        {
            operations.push('(');
        }
        else if (expression[i] == ')')
        {
            while (operations.top() != '(')
            {
                calculate(vectorOfOps, numbers, operations.top());
                operations.pop();
            }
            operations.pop();
        }
        else if (isOperation(vectorOfOps, expression[i]))
        {
            int priorityCurrent = getOp(vectorOfOps, expression[i]).priority;
            while (!operations.empty() && ((getOp(vectorOfOps, expression[i]).association == 'L' && getOp(vectorOfOps, operations.top()).priority >= priorityCurrent) || (getOp(vectorOfOps, expression[i]).association == 'R') && priorityCurrent < getOp(vectorOfOps, operations.top()).priority))
            {
                calculate(vectorOfOps, numbers, operations.top());
                operations.pop();
            }
            operations.push(expression[i]);
        }
        else
        {
            throw incorrect_expression("Invalid token");
        }
    }

    while (!operations.empty())
    {
        calculate(vectorOfOps, numbers, operations.top());
        operations.pop();
    }
    return numbers.top();
}

