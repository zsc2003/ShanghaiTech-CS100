#include "polynomial_parser.hpp"
#include <stack>
#include <iostream>

std::vector<std::string> tokenize(std::string expression) {
    std::string delimiter = " ";
    std::vector<std::string> tokens;
    size_t pos = 0;
    while ((pos = expression.find(delimiter)) != std::string::npos) {
        tokens.push_back(expression.substr(0, pos));
        expression.erase(0, pos + delimiter.length());
    }
    tokens.push_back(expression.substr(0, pos));
    return tokens;
}

Polynomial
PolynomialParser::compute_polynomial(const std::string &expression, std::map<std::string, Polynomial> &polys) {
    std::stack<Polynomial> polyStack;
    std::vector<std::string> tokens = tokenize(expression);
    for (auto token : tokens) {
        if (token == "+") {
            auto p2 = polyStack.top();
            polyStack.pop();
            auto p1 = polyStack.top();
            polyStack.pop();
            polyStack.push(p1 + p2);
        } else if (token == "-") {
            auto p2 = polyStack.top();
            polyStack.pop();
            auto p1 = polyStack.top();
            polyStack.pop();
            polyStack.push(p1 - p2);
        } else if (token == "*") {
            auto p2 = polyStack.top();
            polyStack.pop();
            auto p1 = polyStack.top();
            polyStack.pop();
            polyStack.push(p1 * p2);
        } else {
            auto p = polys[token];
            polyStack.push(p);
        }
    }
    return polyStack.top();
}

// See Piazza @279
PolynomialParser::scalarFct
PolynomialParser::compute_lambda(const std::string &expression, std::map<std::string, Polynomial> &polys) {
    return compute_polynomial(expression, polys);
}