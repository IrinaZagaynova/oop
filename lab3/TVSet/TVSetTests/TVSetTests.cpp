#include "stdafx.h"
#include "../TVSet/TVSet.h"

/*
“елевизор
	изначально выключен
*/

struct TVSetFixture
{
	CTVSet tv;
};

// “елевизор 
BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)
// изначально выключен
BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
{
	BOOST_CHECK(!tv.IsTurnedOn());
}
// не может переключать канал в выключенном состо€нии
BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
{
	BOOST_CHECK(!tv.SelectChannel(87));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
}

// может быть включен
BOOST_AUTO_TEST_CASE(can_be_turned_on)
{
	tv.TurnOn();
	BOOST_CHECK(tv.IsTurnedOn());
}
// изначально отображает 0 канал
BOOST_AUTO_TEST_CASE(displays_channel_0_by_default)
{
	BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
}

struct when_turned_on_ : TVSetFixture
{
	when_turned_on_()
	{
		tv.TurnOn();
	}
};
// после включени€
BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
// отображает канал 1
BOOST_AUTO_TEST_CASE(displays_channel_one)
{
	BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
}
// можно выключить
BOOST_AUTO_TEST_CASE(can_be_turned_off)
{
	tv.TurnOff();
	BOOST_CHECK(!tv.IsTurnedOn());
}

// позвол€ет выбрать канал от 1 до 99
BOOST_AUTO_TEST_CASE(can_select_channel_from_1_to_99)
{
	// ¬ыбираем канал между 1 и 99
	BOOST_CHECK(tv.SelectChannel(1));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

	BOOST_CHECK(tv.SelectChannel(99));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

	BOOST_CHECK(tv.SelectChannel(42));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

	// ѕри попытке выбрать канал за пределами [1; 99] 
	// телевизор не должен мен€ть свой канал
	BOOST_CHECK(!tv.SelectChannel(0));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

	BOOST_CHECK(!tv.SelectChannel(100));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

	tv.TurnOff();
	BOOST_CHECK(!tv.SelectChannel(35));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
}

BOOST_AUTO_TEST_CASE(can_select_previous_channel)
{	
	BOOST_CHECK(tv.SelectPreviousChannel());
	BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

	tv.SelectChannel(2);
	tv.SelectChannel(99);
	BOOST_CHECK(tv.SelectPreviousChannel());
	BOOST_CHECK_EQUAL(tv.GetChannel(), 2);
	BOOST_CHECK(tv.SelectPreviousChannel());
	BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

	tv.TurnOff();
	BOOST_CHECK(!tv.SelectPreviousChannel());
	BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
}

ChannelNumbersAndNames channelNumbersAndNames;

bool CheckChannelNameAndNumberIsInList(int number, const std::string& channelName)
{
	for (auto it = channelNumbersAndNames.begin(); it != channelNumbersAndNames.end();)
		{
			if ((it->first == number) && (it->second == channelName))
			{
				return true;
			}
			it++;
		}
	return false;
}

BOOST_AUTO_TEST_CASE(can_set_channel_name)
{
	BOOST_CHECK(tv.SetChannelName(2, "channel name"));
	channelNumbersAndNames = tv.GetChannelNumbersAndNamesList();
	BOOST_CHECK(CheckChannelNameAndNumberIsInList(2, "channel name"));

	BOOST_CHECK(tv.SetChannelName(3, "3 channel name"));
	channelNumbersAndNames = tv.GetChannelNumbersAndNamesList();
	BOOST_CHECK(CheckChannelNameAndNumberIsInList(3, "3 channel name"));

	BOOST_CHECK(tv.SetChannelName(80, "channel name"));
	channelNumbersAndNames = tv.GetChannelNumbersAndNamesList();
	BOOST_CHECK(CheckChannelNameAndNumberIsInList(80, "channel name"));
	BOOST_CHECK(!CheckChannelNameAndNumberIsInList(2, "channel name"));

	BOOST_CHECK(!tv.SetChannelName(10, ""));
	channelNumbersAndNames = tv.GetChannelNumbersAndNamesList();
	BOOST_CHECK(!CheckChannelNameAndNumberIsInList(10, ""));

	BOOST_CHECK(!tv.SetChannelName(0, ""));
	channelNumbersAndNames = tv.GetChannelNumbersAndNamesList();
	BOOST_CHECK(!CheckChannelNameAndNumberIsInList(0, ""));

	tv.TurnOff();
	BOOST_CHECK(!tv.SetChannelName(2, "name"));
}

BOOST_AUTO_TEST_CASE(can_select_channel_by_name)
{
	tv.SetChannelName(10, "tenth channel name");
	BOOST_CHECK(tv.SelectChannel("tenth channel name"));
	BOOST_CHECK_EQUAL(tv.GetChannel(), 10);

	BOOST_CHECK(!tv.SelectChannel("no channel with this name"));

	tv.TurnOff();
	BOOST_CHECK(!tv.SelectChannel("tenth channel name"));
}

BOOST_AUTO_TEST_CASE(can_delete_channel_name)
{
	BOOST_CHECK(!tv.DeleteChannelName("no channel with this name"));

	tv.SetChannelName(50, "name");
	BOOST_CHECK(tv.DeleteChannelName("name"));
	BOOST_CHECK(!tv.DeleteChannelName("name"));

	tv.SetChannelName(50, "name");
	tv.TurnOff();
	BOOST_CHECK(!tv.DeleteChannelName("name"));
}

BOOST_AUTO_TEST_CASE(can_get_channel_name)
{
	BOOST_CHECK_EQUAL(tv.GetChannelName(5), "");

	tv.SetChannelName(10, "tenth channel name");
	BOOST_CHECK_EQUAL(tv.GetChannelName(10), "tenth channel name");

	tv.SetChannelName(20, "20 channel");
	BOOST_CHECK_EQUAL(tv.GetChannelName(20), "20 channel");

	tv.TurnOff();
	BOOST_CHECK_EQUAL(tv.GetChannelName(20), "");
}

BOOST_AUTO_TEST_CASE(can_get_channel_by_name)
{
	BOOST_CHECK_EQUAL(tv.GetChannelByName("no channel with this name"), 0);

	tv.SetChannelName(10, "tenth channel name");
	BOOST_CHECK_EQUAL(tv.GetChannelByName("tenth channel name"), 10);

	tv.SetChannelName(20, "20 channel");
	BOOST_CHECK_EQUAL(tv.GetChannelByName("20 channel"), 20);

	tv.TurnOff();
	BOOST_CHECK_EQUAL(tv.GetChannelByName("20 channel"), 0);
}

BOOST_AUTO_TEST_SUITE_END()

struct after_subsequent_turning_on_ : when_turned_on_
{
	after_subsequent_turning_on_()
	{
		tv.SelectChannel(33);
		tv.TurnOff();
		tv.TurnOn();
	}
};

// после повторного включени€
BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
// восстанавливает последний выбранный канал
BOOST_AUTO_TEST_CASE(restores_last_selected_channel)
{
	BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
}
BOOST_AUTO_TEST_SUITE_END()

// Ќапишите тесты дл€ недостающего функционала класса CTVSet (если нужно)
//	и дл€ дополнительных заданий на бонусные баллы (если нужно)
// ѕосле написани€ каждого теста убедитесь, что он не проходит.
// ƒоработайте простейшим образом класс CTVSet, чтобы этот тест и предыдущие проходили
// ѕри необходимости выполните рефакторинг кода, сохран€€ работоспособность тестов
// ѕри необходимости используйте вложенные тесты (как использующие fixture, так и нет)
// »мена тестам и test suite-ам давайте такие, чтобы выводима€ в output иерархи€
//	тестов читалась как спецификаци€ на английском €зыке, описывающа€ поведение телевизора

BOOST_AUTO_TEST_SUITE_END()