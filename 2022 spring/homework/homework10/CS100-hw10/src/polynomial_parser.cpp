#include "polynomial_parser.hpp"
#include <sstream>
#include <stack>

Polynomial PolynomialParser::compute_polynomial(const std::string& expression,
    std::map<std::string, Polynomial>& polys) 
{
	std::stringstream input(expression);
	std::string pol;
	std::stack<Polynomial> st;
	while (input >> pol)
	{
		if (pol[0] == '+')
		{
			Polynomial p1 = st.top();
			st.pop();
			Polynomial p2 = st.top();
			st.pop();
			st.push(p2 + p1);
		}
		else if (pol[0] == '-')
		{
			Polynomial p1 = st.top();
			st.pop();
			Polynomial p2 = st.top();
			st.pop();
			st.push(p2 - p1);
		}
		else if (pol[0] == '*')
		{
			Polynomial p1 = st.top();
			st.pop();
			Polynomial p2 = st.top();
			st.pop();
			st.push(p2 * p1);
		}
		else
			st.push(polys[pol]);
	}
	return st.top();
}

std::function<double(double)> PolynomialParser::compute_lambda(const std::string& expression,
    std::map<std::string, Polynomial>& polys)
{
	return compute_polynomial(expression, polys);
}