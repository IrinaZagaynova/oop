#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MiniDictionary/Dictionary.h"

Dictionary dictionary = {
	{ "The Red Square", "Красная Площадь" },
	{ "ball", "мяч" },
	{ "book", "книга" }
};

TEST_CASE("Translate a line already written in the dictionary")
{
	std::string lineTranslation = "";
	REQUIRE(TranslateLine("cat", lineTranslation, dictionary) == false);
	REQUIRE(lineTranslation == "");

	lineTranslation = "";
	REQUIRE(TranslateLine("book", lineTranslation, dictionary) == true);
	REQUIRE(lineTranslation == "книга");

	lineTranslation = "";
	REQUIRE(TranslateLine("The Red Square", lineTranslation, dictionary) == true);
	REQUIRE(lineTranslation == "Красная Площадь");
}

TEST_CASE("Add lines to dictionary")
{
	std::string line = "smth";
	std::string lineTranslation = "";
	REQUIRE(AddLinesToDictionary(line, lineTranslation, dictionary) == false);

	line = "day";
	lineTranslation = "день";
	REQUIRE(AddLinesToDictionary(line, lineTranslation, dictionary) == true);
}

TEST_CASE("Translate the line written in the dictionary by the program function")
{
	std::string lineTranslation = "";
	REQUIRE(TranslateLine("day", lineTranslation, dictionary) == true);
	REQUIRE(lineTranslation == "день");
}