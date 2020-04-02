// HTMLDecode_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTMLDecode/DecodeString.h"

TEST_CASE("Decode empty string gives an empty string")
{
	REQUIRE(DecodeString("").empty());
}

TEST_CASE("Does not change a string without special entities")
{
	std::string str = "string";
	REQUIRE(DecodeString(str) == str);
}

TEST_CASE("Decodes a string with one special entity")
{
	std::string str = "&quot;";
	std::string resultStr = "\"";
	REQUIRE(DecodeString(str) == resultStr);

	str = "123dd&apos;d";
	resultStr = "123dd'd";
	REQUIRE(DecodeString(str) == resultStr);
}

TEST_CASE("Decodes a string with several special entities")
{
	std::string str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string resultStr = "Cat <says> \"Meow\". M&M's";
	REQUIRE(DecodeString(str) == resultStr);
}