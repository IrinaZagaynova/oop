#include "stdafx.h"
#include "../FindMaxEx/FindMax.h"
#include "../FindMaxEx/Sportsman.h"

BOOST_AUTO_TEST_SUITE(FindMax_)

BOOST_AUTO_TEST_CASE(cant_get_the_max_element_in_an_empty_array)
{
	std::vector<int> numbers = {};
	int max = 0;
	BOOST_CHECK(!FindMax(numbers, max, Less<int>));
}

BOOST_AUTO_TEST_CASE(can_get_the_max_element_in_an_array_of_int)
{
	std::vector<int> numbers = { 5, 9, 3, -7 };
	int max = 0;
	BOOST_CHECK(FindMax(numbers, max, Less<int>));
	BOOST_CHECK_EQUAL(max, 9);
}

BOOST_AUTO_TEST_CASE(can_get_the_max_element_in_an_array_of_double)
{
	std::vector<double> numbers = { 5.2, 9.1, 3, -7.6 };
	double max = 0;
	BOOST_CHECK(FindMax(numbers, max, Less<double>));
	BOOST_CHECK_EQUAL(max, 9.1);
}

BOOST_AUTO_TEST_CASE(can_get_the_max_element_in_an_array_of_string)
{
	std::vector<std::string> strings = { "abc", "ba", "ab" };
	std::string max = "";
	BOOST_CHECK(FindMax(strings, max, Less<std::string>));
	BOOST_CHECK_EQUAL(max, "ba");
}

struct SportsmansFixture_
{	
	Sportsman s1 = { "Степанов", "Артём", "Иванович", 175, 75 };
	Sportsman s2 = { "Петров", "Илья", "Александрович", 180.5, 80 };
	Sportsman s3 = { "Васильев", "Михаил", "Сергеевич", 180, 81.5 };
	Sportsman s4 = { "Фёдоров", "Максим", "Андреевич", 170, 65 };

	Sportsman max;
	std::vector<Sportsman> sportsmans = { s1, s2, s3 };
};

BOOST_FIXTURE_TEST_SUITE(SportsmansFixture, SportsmansFixture_)

BOOST_AUTO_TEST_CASE(can_get_a_sportsman_with_max_height)
{	
	BOOST_CHECK(FindMax(sportsmans, max, LessHeight));
	BOOST_CHECK_EQUAL(max.Height, s2.Height);
}

BOOST_AUTO_TEST_CASE(can_get_a_sportsman_with_max_weight)
{
	BOOST_CHECK(FindMax(sportsmans, max, LessWeight));
	BOOST_CHECK_EQUAL(max.Weight, s3.Weight);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()