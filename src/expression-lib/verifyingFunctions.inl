#pragma once
#include <iostream>
#include "expression.h"

enum lastSymbol {
    OPENINGBRACKET = 0,
    CLOSINGBRACKET = 1,
    OPERATION = 2,
    NUMBER = 3
};

bool isNumber(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool isLetter(char ch)
{
    return ch >= 'a' && ch <= 'z';
}

void isNullPtrExpression(const char*& expression)
{
    if (expression == nullptr)
    {
        throw incorrect_expression("Expression is nullptr");

    }
}
bool consistsOf(const char*& expression, char ch)
{
    for (size_t i = 0; i < strlen(expression); i++)
    {
        if (expression[i] != ch)
        {
            return false;
        }
    }
    return true;
}

bool isEmptyExpression(const char*& expression)
{
    return (consistsOf(expression, ' ') || strlen(expression) == 0);
}

bool isFirtsCharacterInvalid(const char*& expression)
{
    return !(isNumber(expression[0]) || (expression[0] == '(') || (expression[0] == '-'));

}
bool isLastCharacterInvalid(const char*& expression)
{
    return !(isNumber(expression[strlen(expression) - 1]) || (expression[strlen(expression) - 1] == ')'));
}

void verifyFirstAndLastCharacter(const char*& expression)
{
    if (isFirtsCharacterInvalid(expression) || isLastCharacterInvalid(expression))
    {
        throw incorrect_expression("First and/or last character of the expression is invalid");
    }
}

void validIntervals(const char*& expression, unsigned position)
{
    if (expression[position + 1] && expression[position + 1] != ' ') throw incorrect_expression("Intervals are not valid");
}

bool validLastSymbol(lastSymbol ls, char ch, std::vector<Ops>& vectorOfOps)
{
    if (ch == '(')
    {
        if (ls == lastSymbol::NUMBER || ls == lastSymbol::CLOSINGBRACKET)
        {
            return false;
        }
    }
    else if (isOperation(vectorOfOps, ch))
    {
        if (ls == lastSymbol::OPERATION || ls == lastSymbol::OPENINGBRACKET)
        {
            return false;
        }
    }
    else if (isNumber(ch))
    {
        if (ls == lastSymbol::NUMBER || ls == lastSymbol::CLOSINGBRACKET)
        {
            return false;
        }
    }
    else if (ch == ')')
    {
        if (ls == lastSymbol::OPERATION || ls == lastSymbol::OPENINGBRACKET)
        {
            return false;
        }
    }
    return true;
}

void verifyIntervalsOperationsOrderAndBracketsInExpression(const char*& expression, std::vector<Ops>& vectorOfOps)
{
    lastSymbol typeOfLastSymbol;
    int countOfBracketsInExpression = 0;

    for (size_t i = 0; i < strlen(expression); i++)
    {
        if (isLetter(expression[i]))
        {
            typeOfLastSymbol = lastSymbol::OPERATION;
            validIntervals(expression, i);
        }
        else if (expression[i] == '-')
        {
            if (expression[i] && expression[i + 1] == ' ') throw incorrect_expression("Invalid unary minus");
        }
        else if (isNumber(expression[i]))
        {
            typeOfLastSymbol = lastSymbol::NUMBER;
            int number = 0;
            while (isNumber(expression[i]))
            {
                number = number * 10 + expression[i] - '0';
                ++i;
            }
            --i;
            validIntervals(expression, i);
        }
        else if (expression[i] == '(')
        {
            typeOfLastSymbol = lastSymbol::OPENINGBRACKET;
            validIntervals(expression, i);
            ++countOfBracketsInExpression;
        }
        else if (expression[i] == ')')
        {
            typeOfLastSymbol = lastSymbol::CLOSINGBRACKET;
            validIntervals(expression, i);
            --countOfBracketsInExpression;
            if (countOfBracketsInExpression < 0) throw incorrect_expression("Invalid brackets");
        }
        else if (expression[i] == ' ')
        {
            if (expression[i + 1] == ' ' || !validLastSymbol(typeOfLastSymbol, expression[i + 1], vectorOfOps))
            {
                throw incorrect_expression("Invalid intervals");
            }
        }
        else
        {
            throw incorrect_expression("Invalid token");
        }

    }
    if (countOfBracketsInExpression)
    {
        throw incorrect_expression("Invalid brackets");
    }
}