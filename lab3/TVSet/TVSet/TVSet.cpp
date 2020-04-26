#include "stdafx.h"
#include "TVSet.h"

CTVSet::ChannelNumbersAndNames CTVSet::GetChannelNumbersAndNamesList()const
{
	return m_channelNumbersAndNames;
}

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

bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn)
	{
		std::swap(m_selectedChannel, m_previousChannel);
		return true;
	}
	return false;
}

bool CTVSet::SetChannelName(int channel, const std::string& channelName)
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

bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	if (m_isOn)
	{
		for (auto it = m_channelNumbersAndNames.begin(); it != m_channelNumbersAndNames.end(); it++)
		{
			if (it->second == channelName)
			{
				m_channelNumbersAndNames.erase(it);
				return true;
			}
		}
	}
	return false;
}

std::string CTVSet::GetChannelName(int channel)const
{
	if (m_isOn)
	{
		auto it = m_channelNumbersAndNames.find(channel);
		if (it != std::end(m_channelNumbersAndNames))
		{
			return it->second;
		}
	}
	return "";
}

int CTVSet::GetChannelByName(const std::string& channelName)const
{
	if (m_isOn)
	{
		for (auto it = m_channelNumbersAndNames.begin(); it != m_channelNumbersAndNames.end(); it++)
		{
			if (it->second == channelName)
			{
				return it->first;
			}
		}
	}
	return 0;
}

bool CTVSet::SelectChannel(const std::string& channelName)
{
	m_previousChannel = m_selectedChannel;
	int channel = GetChannelByName(channelName);
	if (channel > 0)
	{
		m_selectedChannel = channel;
		return true;
	}
	return false;
}