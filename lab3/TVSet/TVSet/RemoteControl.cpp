#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
			{ "TurnOn", [this](istream& strm) {
			   return TurnOn(strm);
			} },
			{ "TurnOff", bind(&CRemoteControl::TurnOff, this, _1) },
			{ "Info", bind(&CRemoteControl::Info, this, _1) },
			{ "SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1) },
			{ "SelectPreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, _1) },
			{ "SetChannelName", bind(&CRemoteControl::SetChannelName, this, _1) },
			{ "DeleteChannelName", bind(&CRemoteControl::DeleteChannelName, this, _1) },
			{ "GetChannelName", bind(&CRemoteControl::GetChannelName, this, _1) },
			{ "GetChannelByName", bind(&CRemoteControl::GetChannelByName, this, _1) },
		})
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
				
}

bool CRemoteControl::TurnOn(std::istream&)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CRemoteControl::TurnOff(std::istream&)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CRemoteControl::Info(std::istream&)
{
	string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\nChannel is: " + to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\n";

	m_output << info;

	CTVSet::ChannelNumbersAndNames channelNumbersAndNamesList = m_tv.GetChannelNumbersAndNamesList();
	for (auto channel : channelNumbersAndNamesList)
	{
		m_output << channel.first << " - " << channel.second << endl;
	}

	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	string str;
	int channel;
	getline(args, str);
	boost::algorithm::trim_all(str);

	if (!m_tv.IsTurnedOn())
	{
		m_output << "Can't select channel because TV is turned off\n";
	}
	else
	{
		if (m_tv.SelectChannel(str))
		{
			m_output << "TV channel changed to " << str << endl;
		}
		else if (((channel = atoi(str.c_str())) > 0) && (m_tv.SelectChannel(channel)))
		{
			m_output << "TV channel changed to " << channel << endl;
		}
		else
		{
			m_output << "Invalid channel\n";
		}
	}
	return true;
}

bool CRemoteControl::SelectPreviousChannel(istream&)
{
	m_tv.SelectPreviousChannel();
	string info = (m_tv.IsTurnedOn())
		? ("TV channel changed to " + to_string(m_tv.GetChannel()) + "\n")
		: "Can't select previous channel because TV is turned off\n";

	m_output << info;

	return true;
}

bool CRemoteControl::SetChannelName(istream& args)
{
	int channel;
	string name;
	args >> channel;
	getline(args, name);
	boost::algorithm::trim_all(name);
	if (!m_tv.SetChannelName(channel, name))
	{
		if (m_tv.IsTurnedOn())
		{
			m_output << "Channel name can't be set\n";
		}
		else
		{
			m_output << "Can't set channel name because TV is turned off\n";
		}
	}
	else
	{
		m_output << "TV channel number " << channel << " is named " << name << endl;
	}

	return true;
}

bool CRemoteControl::DeleteChannelName(istream& args)
{
	string channelName;
	getline(args, channelName);
	boost::algorithm::trim_all(channelName);
	if (!m_tv.DeleteChannelName(channelName))
	{
		if (m_tv.IsTurnedOn())
		{
			m_output << "Can't delete channel name because no channel with that name\n";
		}
		else
		{
			m_output << "Can't delete channel name because TV is turned off\n";
		}
	}
	else
	{
		m_output << "Channel " << channelName << " has been deleted\n";
	}

	return true;
}

bool CRemoteControl::GetChannelName(istream& args)
{
	int channel;
	std::string channelName;
	args >> channel;
	channelName = m_tv.GetChannelName(channel);

	if (!channelName.empty())
	{
		m_output << channelName << endl;
	}
	else
	{
		if (m_tv.IsTurnedOn())
		{
			m_output << "No channel names with that number\n";
		}
		else
		{
			m_output << "Can't get channel name because TV is turned off\n";
		}
	}

	return true;
}

bool CRemoteControl::GetChannelByName(istream& args)
{
	int channel;
	std::string channelName;
	getline(args, channelName);
	boost::algorithm::trim_all(channelName);
	channel = m_tv.GetChannelByName(channelName);

	if (channel != 0)
	{
		m_output << channel << endl;
	}
	else
	{
		if (m_tv.IsTurnedOn())
		{
			m_output << "TV channel " << channelName << " not found\n";
		}
		else
		{
			m_output << "Can't get channel by name because TV is turned off\n";
		}
	}

	return true;
}
