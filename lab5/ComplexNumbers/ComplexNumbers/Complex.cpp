#include "Complex.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include <exception>

CComplex::CComplex(double real, double image)
	: m_real(real), m_image(image)
{
}

CComplex const operator +(CComplex const& complex1, CComplex const& complex2)
{
	return CComplex(complex1.Re() + complex2.Re(), complex1.Im() + complex2.Im());;
}

CComplex const operator -(CComplex const& complex1, CComplex const& complex2)
{
	return CComplex(complex1.Re() - complex2.Re(), complex1.Im() - complex2.Im());
}

CComplex const operator *(CComplex const& complex1, CComplex const& complex2)
{
	double re = complex1.Re() * complex2.Re() - complex1.Im() * complex2.Im();
	double im = complex1.Re() * complex2.Im() + complex1.Im() * complex2.Re();
	return CComplex(re, im);
}

CComplex const operator /(CComplex const& complex1, CComplex const& complex2)
{
	if (complex2.Re() == 0 && complex2.Im() == 0)
	{
		throw std::exception("Error. Division by 0.\n");
	}

	double re = (complex1.Re() * complex2.Re() + complex1.Im() * complex2.Im()) / (pow(complex2.Re(), 2) + pow(complex2.Im(), 2));
	double im = (complex2.Re() * complex1.Im() - complex1.Re() * complex2.Im()) / (pow(complex2.Re(), 2) + pow(complex2.Im(), 2));
	return CComplex(re, im);
}

CComplex const CComplex::operator +() const
{
	return *this;
}

CComplex const CComplex::operator -() const
{
	return CComplex(-m_real, -m_image);
}

CComplex& CComplex::operator +=(CComplex const& complex2)
{
	*this = *this + complex2;
	return *this;
}

CComplex& CComplex::operator -=(CComplex const& complex2)
{
	*this = *this - complex2;
	return *this;
}

CComplex& CComplex::operator *=(CComplex const& complex2)
{
	*this = *this * complex2;
	return *this;
}

CComplex& CComplex::operator /=(CComplex const& complex2)
{	
	*this = *this / complex2;
	return *this;
}

bool CComplex::operator ==(CComplex const& other) const
{
	return (fabs(m_real - other.Re()) < DBL_EPSILON && fabs(m_image - other.Im()) < DBL_EPSILON);
}

bool CComplex::operator !=(CComplex const& other) const
{
	return !(*this == other);
}

std::ostream& operator <<(std::ostream& stream, CComplex const& complex)
{
	stream << complex.Re() << std::showpos << complex.Im() << "i";
	return stream;
}

std::istream& operator >>(std::istream& stream, CComplex& complex)
{
	double re;
	double im;
	if ((stream >> re) && (stream >> im) && (stream.get() == 'i'))
	{
		complex = CComplex(re, im);
	}
	else
	{		
		stream.setstate(std::ios_base::failbit);
	}

	return stream;
}

double CComplex::Re() const
{
	return m_real;
}

double CComplex::Im() const
{
	return m_image;
}

double CComplex::GetMagnitude() const
{
	return sqrt(m_real * m_real + m_image * m_image);
}

double CComplex::GetArgument() const
{
	return atan2(m_image, m_real) * 180 / M_PI;
}
