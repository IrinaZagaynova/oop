#pragma once

class CTVSet
{
public:
	typedef std::map<int, std::string> ChannelNumbersAndNames;
	bool IsTurnedOn()const;
	void TurnOn();
	void TurnOff();
	int GetChannel()const;
	bool SelectChannel(int channel);
	bool SelectChannel(const std::string& channelName);
	bool SelectPreviousChannel();
	bool SetChannelName(int channel, const std::string& channelName);
	ChannelNumbersAndNames GetChannelNumbersAndNamesList()const;
	bool DeleteChannelName(const std::string& channelName);
	std::string GetChannelName(int channel)const;
	int GetChannelByName(const std::string& channelName)const;
private:
	bool m_isOn = false;
	int m_selectedChannel = 1;
	int m_previousChannel = 1;
	ChannelNumbersAndNames m_channelNumbersAndNames;
};
