#include "stdafx.h"
#include "TVSet.h"

bool CTVSet::IsTurnedOn()const
{
	return m_isOn;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

int CTVSet::GetChannel()const
{
	return m_isOn ? m_selectedChannel : 0;
}

bool CTVSet::SelectChannel(int channel)
{
	m_previousChannel = m_selectedChannel;

	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
	if (isAvailableChannel && m_isOn)
	{
		m_selectedChannel = channel;
		return true;
	}
	return false;
}

bool CTVSet::SelectChannel(std::string channelName)
{
	m_previousChannel = m_selectedChannel;

	if (m_isOn)
	{
		for (auto it = m_channelNumbersAndNames.begin(); it != m_channelNumbersAndNames.end();)
		{
			if (it->second == channelName)
			{
				m_selectedChannel = it->first;
				return true;
			}
			it++;
		}		
	}
	return false;
}

bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn)
	{
		int channel = m_selectedChannel;
		m_selectedChannel = m_previousChannel;
		m_previousChannel = channel;
		return true;
	}
	return false;
}

bool CTVSet::SetChannelName(int channel, std::string channelName)
{
	if ((channel < 1 || channel > 99) || (channelName == ""))
	{
		return false;
	}
	
	if (m_isOn)
	{
		DeleteChannelName(channelName);
		m_channelNumbersAndNames.emplace(channel, channelName);
		return true;
	}
	return false;
}

ChannelNumbersAndNames CTVSet::GetChannelNumbersAndNamesList()
{
	return m_channelNumbersAndNames;
}

bool CTVSet::DeleteChannelName(std::string channelName)
{
	if (m_isOn)
	{
		for (auto it = m_channelNumbersAndNames.begin(); it != m_channelNumbersAndNames.end();) 
		{
			if (it->second == channelName)
			{
				m_channelNumbersAndNames.erase(it);
				return true;
			}
			it++;
		}
	}
	return false;
}

std::string CTVSet::GetChannelName(int channel)
{
	if (m_isOn)
	{
		for (auto it = m_channelNumbersAndNames.begin(); it != m_channelNumbersAndNames.end();)
		{
			if (it->first == channel)
			{
				return it->second;
			}
			it++;
		}
	}
	return "";
}

int CTVSet::GetChannelByName(std::string channelName)
{
	if (m_isOn)
	{
		for (auto it = m_channelNumbersAndNames.begin(); it != m_channelNumbersAndNames.end();)
		{
			if (it->second == channelName)
			{
				return it->first;
			}
			it++;
		}
	}
	return 0;
}
