#pragma once
#include <iostream>

class CComplex
{
public:
	CComplex(double real = 0, double image = 0);
	double Re()const;
	double Im()const;
	double GetMagnitude()const;
	double GetArgument()const;

	CComplex const operator +()const;
	CComplex const operator -()const;

	CComplex& operator +=(const CComplex& complex2);
	CComplex& operator -=(const CComplex& complex2);
	CComplex& operator *=(const CComplex& complex2);
	CComplex& operator /=(const CComplex& complex2);

	bool operator ==(const CComplex& other)const;
	bool operator !=(const CComplex& other)const;

private:
	double m_real;
	double m_image;
};

CComplex const operator +(const CComplex& complex1, const CComplex& complex2);
CComplex const operator -(const CComplex& complex1, const CComplex& complex2);
CComplex const operator *(const CComplex& complex1, const CComplex& complex2);
CComplex const operator /(const CComplex& complex1, const CComplex& complex2);

std::ostream& operator <<(std::ostream& stream, const CComplex& complex);
std::istream& operator >>(std::istream& stream, CComplex& complex);