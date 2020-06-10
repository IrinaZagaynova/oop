#pragma once
#include <string>

enum Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol m_protocol,
		unsigned short m_port);

	std::string GetURL()const;
	std::string GetDomain()const;
	std::string GetDocument()const;
	std::string GetProtocolStr()const;
	Protocol GetProtocol()const;
	unsigned short GetPort()const;
private:
	Protocol GetProtocol(std::string protocol)const;
	unsigned short GetDefaultPort(const Protocol& protocol)const;
	std::string GetDocument(const std::string& document)const;
	unsigned short GetPort(const std::string& port, const Protocol& protocol)const;
private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
