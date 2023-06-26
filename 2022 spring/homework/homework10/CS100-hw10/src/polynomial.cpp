#include "polynomial.hpp"
#include <sstream>
#include <fstream>
// Default constructor
Polynomial::Polynomial() {
	while (!m_coeffs.empty())
		m_coeffs.pop_back();
}

//constructor from coefficient vectors (both copy and move versions)
Polynomial::Polynomial(const std::vector<double>& coeffs) : m_coeffs(coeffs) {}
Polynomial::Polynomial(std::vector<double>&& coeffs) : m_coeffs(std::move(coeffs)) {}
//constructor from initializer list
Polynomial::Polynomial(std::initializer_list<double> coeffs) {
	//initializer_list 与 vector 类似,只是其中的元素不能更改
	for (auto coeff : coeffs)
		m_coeffs.push_back(coeff);
}

//constructor from a path to a p*.txt file of coefficients
Polynomial::Polynomial(const std::string& path) {
	puts("1111");
	std::ifstream inFile;
	inFile.open(path);
	puts("2222");
	//std::stringstream input(path);
	std::string coeff;
	while (inFile >> coeff)
		m_coeffs.push_back(stod(coeff));
}

//copy constructor
Polynomial::Polynomial(const Polynomial& p) : m_coeffs(p.m_coeffs) {}
//move constructor
Polynomial::Polynomial(Polynomial&& p) noexcept : m_coeffs(std::move(p.m_coeffs)) {}

//copy and move assignments
Polynomial& Polynomial::operator=(const Polynomial& p) {
	m_coeffs = p.m_coeffs;
	return *this;
}
Polynomial& Polynomial::operator=(Polynomial&& p) noexcept {
	m_coeffs = std::move(p.m_coeffs);
	return *this;
}

//destructor
Polynomial::~Polynomial() {
	while (!m_coeffs.empty())
		m_coeffs.pop_back();
}

//access to polynomial coefficients
double& Polynomial::operator[](int index) {
	return m_coeffs[index];
}
const double& Polynomial::operator[](int index) const {
	return m_coeffs[index];
}

//get number of coefficients (equals degree)
int Polynomial::size() const {
	return m_coeffs.size();
}

//functional operations (self-explanatory)
Polynomial Polynomial::operator+ (const Polynomial& p) const {
	int len = size();
	int num = 0;
	Polynomial add(m_coeffs);
	for (auto coeff : p.m_coeffs)
	{
		if (num >= len)
			add.m_coeffs.push_back(coeff);
		else
			add.m_coeffs[num] += coeff;
		num++;
	}
	return add;
}
Polynomial& Polynomial::operator+=(const Polynomial& p) {
	int len = size();
	int num = 0;
	for (auto coeff : p.m_coeffs)
	{
		if (num >= len)
			m_coeffs.push_back(coeff);
		else
			m_coeffs[num] += coeff;
		num++;
	}
	return *this;
}
Polynomial Polynomial::operator- (const Polynomial& p) const {
	int len = size();
	int num = 0;
	Polynomial minus(m_coeffs);
	for (auto coeff : p.m_coeffs)
	{
		if (num >= len)
			minus.m_coeffs.push_back(-1.0*coeff);
		else
			minus.m_coeffs[num] -= coeff;
		num++;
	}
	return minus;
}
Polynomial& Polynomial::operator-=(const Polynomial& p) {
	int len = size();
	int num = 0;
	for (auto coeff : p.m_coeffs)
	{
		if (num >= len)
			m_coeffs.push_back(-1.0*coeff);
		else
			m_coeffs[num] -= coeff;
		num++;
	}
	return *this;
}
Polynomial Polynomial::operator* (const Polynomial& p) const {
	Polynomial times;
	int l1 = size(), l2 = p.size();
	int len = l1 + l2 - 1;
	for (int i = 0;i < len;++i)
		times.m_coeffs.push_back(0);
	for (int i = 0;i < l1;++i)
		for (int j = 0;j < l2;++j)
			times.m_coeffs[i + j] += m_coeffs[i] * p.m_coeffs[j];
	return times;
}
Polynomial Polynomial::operator* (double factor) const {
	Polynomial times(m_coeffs);
	int len = size();
	for (int i = 0;i < len;++i)
		times.m_coeffs[i] *= factor;
	return times;
}
Polynomial& Polynomial::operator*=(const Polynomial& p) {
	Polynomial times;
	int l1 = size(), l2 = p.size();
	int len = l1 + l2 - 1;
	for (int i = 0;i < len;++i)
		times.m_coeffs.push_back(0);
	for (int i = 0;i < l1;++i)
		for (int j = 0;j < l2;++j)
			times.m_coeffs[i + j] += m_coeffs[i] * p.m_coeffs[j];
	while (!m_coeffs.empty())
		m_coeffs.pop_back();
	for (auto coeff : times.m_coeffs)
		m_coeffs.push_back(coeff);
	return *this;
}

//function (polynomial) evaluation
double Polynomial::operator()(double x) const {
	double ans = 0.0;
	double num = 1.0;
	for (auto coeff : m_coeffs)
	{
		ans += coeff * num;
		num *= x;
	}
	return ans;
}