#ifndef CS100_HW10_POLYNOMIAL_HPP_
#define CS100_HW10_POLYNOMIAL_HPP_

#include <vector>
#include <string>

class Polynomial {
public:
	// Default constructor
	Polynomial();

	//constructor from coefficient vectors (both copy and move versions)
	Polynomial( const std::vector<double> & coeffs );
	Polynomial( std::vector<double> && coeffs );
	//constructor from initializer list
	Polynomial( std::initializer_list<double> coeffs );

	//constructor from a path to a p*.txt file of coefficients
	Polynomial( const std::string & path );

	//copy constructor
	Polynomial( const Polynomial & p );
	//move constructor
	Polynomial( Polynomial && p ) noexcept ;

	//copy and move assignments
	Polynomial & operator=(const Polynomial & p);
	Polynomial & operator=( Polynomial && p ) noexcept ;

	//destructor
	virtual ~Polynomial();

	//access to polynomial coefficients
	double & operator[](int index);
	const double & operator[](int index) const;

	//get number of coefficients (equals degree)
	int size() const;

	//functional operations (self-explanatory)
	Polynomial   operator+ (const Polynomial & p) const;
	Polynomial & operator+=(const Polynomial & p);
	Polynomial   operator- (const Polynomial & p) const;
	Polynomial & operator-=(const Polynomial & p);
	Polynomial   operator* (const Polynomial & p) const;
	Polynomial   operator* (double factor) const;
	Polynomial & operator*=(const Polynomial & p);

	//function (polynomial) evaluation
	double operator()( double x ) const;

private:
	std::vector<double> m_coeffs;
};

#endif
