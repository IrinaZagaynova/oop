#include "stdafx.h"
#include "../TVSet/RemoteControl.h"
#include "../TVSet/TVSet.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

// Зависимости RemoteControl-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструирования самого remote-контрола
struct RemoteControlDependencies
{
	CTVSet tv;
	stringstream input;
	stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;

	RemoteControlFixture()
		: remoteControl(tv, input, output)
	{
	}

	// Вспомогательная функция для проверки работы команды command
	// Она принимает ожидаемый номер канала expectedChannel и expectedOutput
	void VerifyCommandHandling(const string& command, const optional<int>& expectedChannel, const string& expectedOutput)
	{
		// Предварительно очищаем содержимое выходного потока
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), expectedChannel.is_initialized());
		BOOST_CHECK_EQUAL(tv.GetChannel(), expectedChannel.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)

BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
{
	VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
}

BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
{
	tv.TurnOn();
	VerifyCommandHandling("TurnOff", none, "TV is turned off\n");
}

BOOST_AUTO_TEST_CASE(can_print_tv_info)
{
	// Ожидаемое поведение команды Info, вызванной у выключенного телевизора
	VerifyCommandHandling("Info", none, "TV is turned off\n");

	// Проверяем поведение команды Info у включенного телевизора
	tv.TurnOn();
	tv.SelectChannel(42);
	VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n");
	
	// Проверяем поведение команды Info у включенного телевизора, когда задан список имён каналов
	tv.SetChannelName(17, "Discovery");
	tv.SetChannelName(1, "1 channel");
	tv.SelectChannel(5);
	VerifyCommandHandling("Info", 5, "TV is turned on\nChannel is: 5\n1 - 1 channel\n17 - Discovery\n");
}

BOOST_AUTO_TEST_CASE(can_select_a_valid_channel_by_number_when_tv_is_on)
{
	tv.TurnOn();
	VerifyCommandHandling("SelectChannel 42", 42, "TV channel changed to 42\n");
}

BOOST_AUTO_TEST_CASE(can_select_a_valid_channel_by_name_when_tv_is_on)
{
	tv.TurnOn();
	tv.SetChannelName(10, "name of channel 10");
	VerifyCommandHandling("SelectChannel name of channel 10", 10, "TV channel changed to name of channel 10\n");
	VerifyCommandHandling("SelectChannel  name    of   channel  10  ", 10, "TV channel changed to name of channel 10\n");

	tv.SetChannelName(20, "20 channel");
	VerifyCommandHandling("SelectChannel   20   channel   ", 20, "TV channel changed to 20 channel\n");
}

BOOST_AUTO_TEST_CASE(cant_select_channel_when_tv_turned_off)
{
	VerifyCommandHandling("SelectChannel 42", none, "Can't select channel because TV is turned off\n");
	VerifyCommandHandling("SelectChannel 100", none, "Can't select channel because TV is turned off\n");
}

BOOST_AUTO_TEST_CASE(cant_select_an_invalid_channel_when_tv_is_on)
{
	tv.TurnOn();
	tv.SelectChannel(42);
	VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel\n");
	VerifyCommandHandling("SelectChannel nonexistent channel", 42, "Invalid channel\n");
	VerifyCommandHandling("SelectChannel", 42, "Invalid channel\n");
}

BOOST_AUTO_TEST_CASE(can_select_previous_channel_when_tv_is_on)
{
	tv.TurnOn();
	tv.SelectChannel(35);
	tv.SelectChannel(42);
	VerifyCommandHandling("SelectPreviousChannel", 35, "TV channel changed to 35\n");
}

BOOST_AUTO_TEST_CASE(cant_select_previous_channel_when_tv_is_turned_off)
{
	tv.SelectPreviousChannel();
	VerifyCommandHandling("SelectPreviousChannel", none, "Can't select previous channel because TV is turned off\n");
}

BOOST_AUTO_TEST_CASE(can_set_channel_name_when_tv_is_on)
{
	tv.TurnOn();
	VerifyCommandHandling("SetChannelName 10 some name", 1, "TV channel number 10 is named some name\n");
	VerifyCommandHandling("SetChannelName 10     some     name    ", 1, "TV channel number 10 is named some name\n");
	VerifyCommandHandling("SetChannelName 10   10  channel  ", 1, "TV channel number 10 is named 10 channel\n");
}

BOOST_AUTO_TEST_CASE(cant_set_channel_name_when_tv_is_turned_off)
{
	VerifyCommandHandling("SetChannelName 10 name", none, "Can't set channel name because TV is turned off\n");
}

BOOST_AUTO_TEST_CASE(cant_set_channel_name_when_tv_is_on_and_invalid_data_entered)
{
	tv.TurnOn();
	VerifyCommandHandling("SetChannelName 10", 1, "Channel name can't be set\n");
	VerifyCommandHandling("SetChannelName name", 1, "Channel name can't be set\n");
	VerifyCommandHandling("SetChannelName 100 name", 1, "Channel name can't be set\n");
}

BOOST_AUTO_TEST_CASE(can_delete_channel_name_when_tv_is_on_and_entered_name_was_set)
{
	tv.TurnOn();
	tv.SetChannelName(10, "some name");
	VerifyCommandHandling("DeleteChannelName some name", 1, "Сhannel some name has been deleted\n");
	tv.SetChannelName(10, "some name");
	VerifyCommandHandling("DeleteChannelName  some  name  ", 1, "Сhannel some name has been deleted\n");
}

BOOST_AUTO_TEST_CASE(cant_delete_channel_name_when_tv_is_turned_off)
{
	VerifyCommandHandling("DeleteChannelName name", none, "Can't delete channel name because TV is turned off\n");
}

BOOST_AUTO_TEST_CASE(cant_delete_channel_name_when_tv_is_on_and_entered_name_wasnt_set)
{
	tv.TurnOn();
	VerifyCommandHandling("DeleteChannelName name", 1, "Can't delete channel name because no channel with that name\n");
}

BOOST_AUTO_TEST_CASE(can_get_channel_name_if_it_was_set_when_tv_is_on)
{
	tv.TurnOn();
	tv.SetChannelName(5, "fifth channel name");
	VerifyCommandHandling("GetChannelName 5", 1, "fifth channel name\n");
}

BOOST_AUTO_TEST_CASE(cant_get_channel_name_if_it_wasnt_set_when_tv_is_on)
{
	tv.TurnOn();
	VerifyCommandHandling("GetChannelName 2", 1, "No channel names with that number\n");
}

BOOST_AUTO_TEST_CASE(cant_get_channel_name_when_tv_is_turned_off)
{
	VerifyCommandHandling("GetChannelName 2", none, "Can't get channel name because TV is turned off\n");
}

BOOST_AUTO_TEST_CASE(can_get_channel_by_name_if_it_was_set_when_tv_is_on)
{
	tv.TurnOn();
	tv.SetChannelName(5, "fifth channel name");
	VerifyCommandHandling("GetChannelByName fifth channel name", 1, "5\n");
}

BOOST_AUTO_TEST_CASE(cant_get_channel_by_name_if_it_wasnt_set_when_tv_is_on)
{
	tv.TurnOn();
	VerifyCommandHandling("GetChannelByName fifth channel name", 1, "TV channel fifth channel name not found\n");
}

BOOST_AUTO_TEST_CASE(cant_get_channel_by_name__when_tv_is_turned_off)
{
	VerifyCommandHandling("GetChannelByName name", none, "Can't get channel by name because TV is turned off\n");
}

BOOST_AUTO_TEST_SUITE_END()