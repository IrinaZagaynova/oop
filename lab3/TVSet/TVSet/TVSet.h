#pragma once

typedef std::map<int, std::string> ChannelNumbersAndNames;

class CTVSet
{
public:
	bool IsTurnedOn()const;
	void TurnOn();
	void TurnOff();
	int GetChannel()const;
	bool SelectChannel(int channel);
	bool SelectChannel(std::string channelName);
	bool SelectPreviousChannel();
	bool SetChannelName(int channel, std::string channelName);
	ChannelNumbersAndNames GetChannelNumbersAndNamesList()const;
	bool DeleteChannelName(std::string channelName);
	std::string GetChannelName(int channel)const;
	int GetChannelByName(std::string channelName)const;
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_previousChannel = 1;
	ChannelNumbersAndNames m_channelNumbersAndNames;
};
