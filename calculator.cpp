﻿#include <iostream>
#include <string>
#include <stack>
#include "AbstractCalculator.h"

using namespace std;

class Calculator : public AbstractCalculator {
public:
    double calculate(const string& input) override;

private:
    static double Action(double num1, double num2, char op);
    static int NextActionDetector(const string& input, int startIndex, int endIndex);
};

double Calculator::Action(double num1, double num2, char op) {
    switch (op) {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    default:
        return 0;
    }
}

int Calculator::NextActionDetector(const string& input, int startIndex, int endIndex) {
    int parenthesesCounter = 0;
    for (int i = endIndex; i >= startIndex; --i) {
        if (input[i] == ')')
            parenthesesCounter++;
        else if (input[i] == '(')
            parenthesesCounter--;
        else if ((input[i] == '+' || input[i] == '-') && parenthesesCounter == 0)
            return i;
    }

    for (int i = endIndex; i >= startIndex; --i) {
        if (input[i] == ')')
            parenthesesCounter++;
        else if (input[i] == '(')
            parenthesesCounter--;
        else if ((input[i] == '*' || input[i] == '/') && parenthesesCounter == 0)
            return i;
    }

    return -1; // Return -1 if no operation found
}

double Calculator::calculate(const string& input) {
    stack<char> operatorStack;
    stack<double> operandStack;

    for (int i = 0; i < input.size(); ++i) {
        if (isdigit(input[i])) {
            string numStr;
            while (i < input.size() && (isdigit(input[i]) || input[i] == '.')) {
                numStr += input[i];
                i++;
            }
            i--;

            double num = stod(numStr);
            operandStack.push(num);
        }
        else if (input[i] == '(') {
            operatorStack.push(input[i]);
        }
        else if (input[i] == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                char op = operatorStack.top();
                operatorStack.pop();

                double num2 = operandStack.top();
                operandStack.pop();
                double num1 = operandStack.top();
                operandStack.pop();

                double result = Action(num1, num2, op);
                operandStack.push(result);
            }

            if (!operatorStack.empty() && operatorStack.top() == '(') {
                operatorStack.pop();
            }
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            while (!operatorStack.empty() && operatorStack.top() != '(' && ((input[i] == '*' || input[i] == '/') || (input[i] == '+' || input[i] == '-') && (operatorStack.top() == '*' || operatorStack.top() == '/'))) {
                char op = operatorStack.top();
                operatorStack.pop();

                double num2 = operandStack.top();
                operandStack.pop();
                double num1 = operandStack.top();
                operandStack.pop();

                double result = Action(num1, num2, op);
                operandStack.push(result);
            }

            operatorStack.push(input[i]);
        }
    }

    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();

        double num2 = operandStack.top();
        operandStack.pop();
        double num1 = operandStack.top();
        operandStack.pop();

        double result = Action(num1, num2, op);
        operandStack.push(result);
    }

    return operandStack.top();
}

AbstractCalculator* AbstractCalculator::createCalculator() {
    return new Calculator();
}

int main() {
    string input;
    cout << "Enter an expression with parentheses: ";
    getline(cin, input);

    // Создание объекта Calculator с использованием фабричного метода из AbstractCalculator
    AbstractCalculator* calculator = AbstractCalculator::createCalculator();

    // Использование калькулятора для вычисления выражения
    double result = calculator->calculate(input);
    cout << "Result: " << result << endl;

    // Очистка
    delete calculator;

    return 0;
}