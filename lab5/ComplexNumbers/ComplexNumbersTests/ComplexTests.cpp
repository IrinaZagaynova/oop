#include "../ComplexNumbers/Complex.h"
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"

CComplex A(5, 10);
CComplex B(4, 2);

TEST_CASE("Must return the real part of a complex number")
{
	CHECK(A.Re() == 5);
}

TEST_CASE("Must return the imaginary part of a complex number")
{
	CHECK(A.Re() == 5);
}

TEST_CASE("Must return the modulus of a complex number")
{
	CHECK(A.GetMagnitude() - 11.1803 < 0.0001);
}

TEST_CASE("Must return an argument of a complex number")
{
	CHECK(A.GetArgument() - 63.4349 < 0.0001);
}

TEST_CASE("Binary plus should adds up complex numbers")
{
	CComplex C = A + B;
	CHECK(C.Re() == 9);
	CHECK(C.Im() == 12);
}

TEST_CASE("Binary plus should adds up a complex number and a real number")
{	
	CComplex C = 5.6 + A;
	CHECK(C.Re() == 10.6);
	CHECK(C.Im() == 10);
		
	C = B + 5.6;
	CHECK(C.Re() == 9.6);
	CHECK(C.Im() == 2);
}

TEST_CASE("Binary minus should subtracts a complex number from a complex number")
{
	CComplex C = A - B;
	CHECK(C.Re() == 1);
	CHECK(C.Im() == 8);
}

TEST_CASE("Binary minus should get the difference of a complex number and a real number")
{
	CComplex C = A - 5;
	CHECK(C.Re() == 0);
	CHECK(C.Im() == 10);

	C = 5 - B;
	CHECK(C.Re() == 1);
	CHECK(C.Im() == -2);
}

TEST_CASE("Multiplication should multiply complex numbers")
{
	CComplex C = A * B;
	CHECK(C.Re() == 0);
	CHECK(C.Im() == 50);
}

TEST_CASE("Multiplication should multiply a complex number and a real number")
{
	CComplex C = A * 3;
	CHECK(C.Re() == 15);
	CHECK(C.Im() == 30);

	C = 3 * B;
	CHECK(C.Re() == 12);
	CHECK(C.Im() == 6);
}

TEST_CASE("Division should divide a complex number by a complex number")
{
	CComplex C = A / B;
	CHECK(C.Re() == 2);
	CHECK(C.Im() == 1.5);
}

TEST_CASE("Mustn't divide a complex number by zero")
{
	CComplex C(0, 0);
	CHECK_THROWS(A / C);
	CHECK_THROWS(A / 0);
}

TEST_CASE("Division should get the quotient of a complex number and a real number")
{
	CComplex C = A / 5;
	CHECK(C.Re() == 1);
	CHECK(C.Im() == 2);

	C = 5 / B;
	CHECK(C.Re() == 1);
	CHECK(C.Im() == -0.5);
}

TEST_CASE("Unary plus should return a copy of a complex number")
{
	CComplex C = +A;
	CHECK(C.Re() == 5);
	CHECK(C.Im() == 10);
}

TEST_CASE("Unary minus should return the opposite complex number")
{
	CComplex C = -A;
	CHECK(C.Re() == -5);
	CHECK(C.Im() == -10);
}

TEST_CASE("+= must add to the complex number combining with the assignment")
{
	CComplex C(5, 10);
	C += B;
	CHECK(C.Re() == 9);
	CHECK(C.Im() == 12);

	C += 4;
	CHECK(C.Re() == 13);
	CHECK(C.Im() == 12);
}

TEST_CASE("-= must subtract from a complex number combining with the assignment")
{
	CComplex C(5, 10);
	C -= B;
	CHECK(C.Re() == 1);
	CHECK(C.Im() == 8);

	C -= 4;
	CHECK(C.Re() == -3);
	CHECK(C.Im() == 8);
}

TEST_CASE("*= must multiply a complex number combining with the assignment")
{
	CComplex C(6, -4);
	C *= B;
	CHECK(C.Re() == 32);
	CHECK(C.Im() == -4);
	
	C *= 2;
	CHECK(C.Re() == 64);
	CHECK(C.Im() == -8);
}

TEST_CASE("/= must divide a complex number combining with the assignment")
{
	CComplex C(6, -4);
	C /= B;
	CHECK(C.Re() == 0.8);
	CHECK(C.Im() == -1.4);

	C /= 4;
	CHECK(C.Re() == 0.2);
	CHECK(C.Im() == -0.35);
}

TEST_CASE("/= mustn't divide a complex number by zero combining with the assignment")
{
	CComplex C(0, 0);
	CHECK_THROWS(A /= C);
	CHECK_THROWS(A /= 0);
}

TEST_CASE("== сompares a complex numbers with a complex number")
{
	CComplex C(5, 10);
	CHECK(C == A);

	CHECK(!(A == B));
}

TEST_CASE("!= must check complex numbers for the inequality")
{
	CHECK(A != B);

	CComplex A(5, 10);
	CHECK(!(A != A));
}

TEST_CASE("Input operator should read a complex numbers")
{
	CComplex C;
	(std::stringstream)"-3.5-4.8i" >> C;
	CHECK(C.Re() == -3.5);
	CHECK(C.Im() == -4.8);

	(std::stringstream)"4+2i" >> C;
	CHECK(C.Re() == 4);
	CHECK(C.Im() == 2);
}

TEST_CASE("If complex number failed to read, stream has a failbit state")
{
	CComplex C;
	std::stringstream strm;
	strm << "4+2";
	strm >> C;
	CHECK(strm.fail());
}

TEST_CASE("Output operator should print a complex number")
{
	CComplex C(-3.5, -4.8);
	std::stringstream strmC;
	strmC << C;
	CHECK(strmC.str() == "-3.5-4.8i");

	CComplex D(4, 2);
	std::stringstream strmD;
	strmD << D;
	CHECK(strmD.str() == "4+2i");
}