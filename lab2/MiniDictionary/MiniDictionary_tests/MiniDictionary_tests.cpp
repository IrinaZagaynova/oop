#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MiniDictionary/Dictionary.h"

Dictionary dictionary = {
	{ "the red square", "Красная Площадь" },
	{ "ball", "мяч" },
	{ "cat", "кот, кошка" }
};

TEST_CASE("Words from file must be added to dictionary")
{
	std::istringstream streamInput("the red square\nКрасная Площадь\nball\nмяч\ncat\nкот, кошка\n");
	Dictionary inputDictionary;

	FillInDictionaryFromFile(streamInput, inputDictionary);
	REQUIRE(inputDictionary == dictionary);
}

TEST_CASE("Сheck the addition of words to the dictionary")
{
	std::string line = "word";
	std::string translation = "";
	REQUIRE(AddLinesToDictionary(line, translation, dictionary) == false);

	line = "day";
	translation = "день";
	REQUIRE(AddLinesToDictionary(line, translation, dictionary) == true);
}

TEST_CASE("Lines written in the dictionary must be translated")
{
	std::string translation = "";
	REQUIRE(TranslateLine("meat", translation, dictionary) == false);
	REQUIRE(translation == "");

	translation = "";
	REQUIRE(TranslateLine("cat", translation, dictionary) == true);
	REQUIRE(translation == "кот, кошка");

	translation = "";
	REQUIRE(TranslateLine("bALl", translation, dictionary) == true);
	REQUIRE(translation == "мяч");

	translation = "";
	REQUIRE(TranslateLine("The Red Square", translation, dictionary) == true);
	REQUIRE(translation == "Красная Площадь");

	translation = "";
	REQUIRE(TranslateLine("day", translation, dictionary) == true);
	REQUIRE(translation == "день");
}

TEST_CASE("Words from dictionary must be added to file")
{
	std::ostringstream streamOutput;
	std::ostringstream expectedStreamOutput("ball\nмяч\ncat\nкот, кошка\nday\nдень\nthe red square\nКрасная Площадь\n");

	SaveDictionaryToFile(dictionary, streamOutput);
	REQUIRE(streamOutput.str() == expectedStreamOutput.str());
}

