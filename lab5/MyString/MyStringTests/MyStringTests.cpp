#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MyString/MyString.h"

TEST_CASE("Can create СMyString object")
{
	CMyString str;
	CHECK(str.GetStringData() == nullptr);
	CHECK(str.GetLength() == 0);
}

TEST_CASE("Can create СMyString object from string data with a terminating null character")
{
	CMyString str("line");
	CHECK(str.GetStringData() == std::string("line"));
	CHECK(str.GetLength() == 4);
	
	CMyString str2("line\0line");
	CHECK(str2.GetStringData() == std::string("line"));
	CHECK(str2.GetLength() == 4);
}

TEST_CASE("Can create СMyString object from a character array of a given length")
{
	CMyString str("characters", 4);
	CHECK(str.GetStringData() == std::string("char"));
	CHECK(str.GetLength() == 4);

	CMyString str2("ch\0aracters", 4);
	CHECK(str2.GetStringData() == std::string("ch\0ar"));
	CHECK(str2.GetLength() == 4);

	CMyString str3("ch\0aracters", 15);
	CHECK(str3.GetStringData() == std::string("ch\0aracters"));
	CHECK(str3.GetLength() == 15);
}

TEST_CASE("Can create СMyString object from a std::string")
{
	std::string str = "string";
	CMyString myString(str);
	CHECK(myString.GetStringData() == str);
	CHECK(myString.GetLength() == 6);
}

TEST_CASE("СMyString object can be copied")
{
	CMyString str("line");
	CMyString copy(str);
	CHECK(std::string(str.GetStringData()) == std::string(copy.GetStringData()));
	CHECK(str.GetLength() == copy.GetLength());
}

TEST_CASE("Can return a substring from a given position no longer than length characters")
{
	CMyString str("some line");
	CMyString result = str.SubString(0, 5);
	CHECK(result.GetStringData() == std::string("some "));
	CHECK(result.GetLength() == 5);

	result = str.SubString(5, 2);
	CHECK(result.GetStringData() == std::string("li"));
	CHECK(result.GetLength() == 2);

	result = str.SubString(5, 15);
	CHECK(result.GetStringData() == std::string("line"));
	CHECK(result.GetLength() == 4);
}

TEST_CASE("Clear() can clear CMyString object")
{
	CMyString str("line");
	str.Clear();
	CHECK(str.GetStringData() == std::string(""));
	CHECK(str.GetLength() == 0);
}

TEST_CASE("= assigns a value to СMyString object")
{
	CMyString str("line");
	str = str;
	CHECK(str.GetStringData() == std::string("line"));
	CHECK(str.GetLength() == 4);

	str = "characters";
	CHECK(str.GetStringData() == std::string("characters"));
	CHECK(str.GetLength() == 10);

	CMyString str2 = str;
	CHECK(std::string(str.GetStringData()) == std::string(str2.GetStringData()));
	CHECK(str.GetLength() == str2.GetLength());

	std::string str3 = "string";
	str = str3;
	CHECK(str.GetStringData() == std::string("string"));
	CHECK(str.GetLength() == 6);
}

TEST_CASE("+ can concatenate СMyString objects")
{
	CMyString str1("str1");
	CMyString str2("str2");
	CMyString str3("str3");

	CMyString result = str1 + str2 + str3;
	CHECK(result.GetStringData() == std::string("str1str2str3"));
	CHECK(result.GetLength() == 12);

	result = str1 + "characters";
	CHECK(result.GetStringData() == std::string("str1characters"));
	CHECK(result.GetLength() == 14);

	std::string str4= "string";
	result = str1 + str4;
	CHECK(result.GetStringData() == std::string("str1string"));
	CHECK(result.GetLength() == 10);
}

TEST_CASE("== can compare СMyString objects")
{
	CMyString str1("line");
	CMyString str2("line");

	CHECK(str1 == str2);
	str2 = "line ";
	CHECK(!(str1 == str2));
	str2 = "lin1";
	CHECK(!(str1 == str2));
}

TEST_CASE("!= can check СMyString objects for inequality")
{
	CMyString str1("line");
	CMyString str2("line");

	CHECK(!(str1 != str2));
	str2 = "line ";
	CHECK(str1 != str2);
	str2 = "lin1";
	CHECK(str1 != str2);
}

TEST_CASE("< can lexicographically compare strings, return true if the line to the left precedes the line to the right")
{
	CMyString str1("abc");
	CMyString str2("abd");
	CHECK(str1 < str2);
	CHECK(!(str2 < str1));

	str2 = "ab";
	CHECK(str2 < str1);
	CHECK(!(str1 < str2));

	str1 = "ab";
	CHECK(!(str2 < str1));
	CHECK(!(str1 < str2));
}

TEST_CASE("> can lexicographically compare strings, return true if the line to the right precedes the line to the left")
{
	CMyString str1("abd");
	CMyString str2("abc");
	CHECK(str1 > str2);
	CHECK(!(str2 > str1));

	str1 = "ab";
	CHECK(str2 > str1);
	CHECK(!(str1 > str2));

	str2 = "ab";
	CHECK(!(str2 > str1));
	CHECK(!(str1 > str2));
}

TEST_CASE("<= can lexicographically compare strings, return true if the line to the left precedes the line to the right or lines equal")
{
	CMyString str1("abc");
	CMyString str2("abd");
	CHECK(str1 <= str2);
	CHECK(!(str2 <= str1));

	str2 = "ab";
	CHECK(str2 <= str1);
	CHECK(!(str1 <= str2));

	str1 = "ab";
	CHECK(str2 <= str1);
}

TEST_CASE(">= can lexicographically compare strings, return true if the line to the right precedes the line to the left or lines equal")
{
	CMyString str1("abd");
	CMyString str2("abc");
	CHECK(str1 >= str2);
	CHECK(!(str2 >= str1));

	str1 = "ab";
	CHECK(str2 >= str1);
	CHECK(!(str1 >= str2));

	str2 = "ab";
	CHECK(str2 >= str1);
}

TEST_CASE("[] can get indexed access to string characters for reading")
{
	CMyString str("line");
	CHECK(str[3] == 'e');
}

TEST_CASE("[] can get indexed access to string characters for writing")
{
	CMyString str("line");
	str[3] = '1';
	CHECK(str[3] == '1');
}
