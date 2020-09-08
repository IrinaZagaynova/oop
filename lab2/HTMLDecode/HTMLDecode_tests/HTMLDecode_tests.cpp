// HTMLDecode_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../HTMLDecode/DecodeString.h"

TEST_CASE("Decode empty string gives an empty string")
{
	CHECK(DecodeString("") == "");
}

TEST_CASE("Does not change a string without special entities")
{
	std::string str = "&quot amp;";
	CHECK(DecodeString(str) == str);
}

TEST_CASE("Decodes a string with special entities")
{
	std::string str = "&quot;";
	std::string expected = "\"";
	CHECK(DecodeString(str) == expected);

	str = "&lt;str";
	expected = "<str";
	CHECK(DecodeString(str) == expected);

	str = "str&amp;";
	expected = "str&";
	CHECK(DecodeString(str) == expected);

	str = "str&apos;str";
	expected = "str'str";
	CHECK(DecodeString(str) == expected);

	str = "&amp;lt;";
	expected = "&lt;";
	CHECK(DecodeString(str) == expected);

	str = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	expected = "Cat <says> \"Meow\". M&M's";
	CHECK(DecodeString(str) == expected);
}

