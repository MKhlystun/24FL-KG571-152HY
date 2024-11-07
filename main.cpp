#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "error.h"

class Calculator {
private:
    // Function to determine precedence of operators
    int precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    // Function to apply an operation to two operands
    double applyOperation(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/':
                if (b == 0) throw std::invalid_argument("Division by zero");
                return a / b;
            default: throw std::invalid_argument("Unknown operator");
        }
    }

public:
    // Function to evaluate a given infix expression
    double evaluate(const std::string& expression) {
        std::stack<double> values;     // Stack to store numbers
        std::stack<char> ops;          // Stack to store operators

        for (size_t i = 0; i < expression.length(); ++i) {
            // Skip whitespaces
            if (isspace(expression[i])) continue;

            // If current character is a number, parse it as a number
            if (isdigit(expression[i]) || expression[i] == '.') {
                std::stringstream ss;
                while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                    ss << expression[i++];
                }
                --i; // to counter the last increment in the loop
                values.push(std::stod(ss.str()));
            }
            // If current character is an '(', push it to 'ops'
            else if (expression[i] == '(') {
                ops.push(expression[i]);
            }
            // If current character is ')', solve the sub-expression
            else if (expression[i] == ')') {
                while (!ops.empty() && ops.top() != '(') {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOperation(val1, val2, op));
                }
                ops.pop(); // Remove '('
            }
            // If the character is an operator, process it
            else if (expression[i] == '+' || expression[i] == '-' ||
                     expression[i] == '*' || expression[i] == '/') {
                while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    char op = ops.top(); ops.pop();
                    values.push(applyOperation(val1, val2, op));
                }
                ops.push(expression[i]);
            }
        }

        // Process remaining operations
        while (!ops.empty()) {
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            char op = ops.top(); ops.pop();
            values.push(applyOperation(val1, val2, op));
        }

        // The final result is in the values stack
        return values.top();
    }
};

int main() {
    Calculator calculator;
    std::string expression;

    std::cout << "Enter an infix expression: ";
    std::getline(std::cin, expression);

    try {
        double result = calculator.evaluate(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

