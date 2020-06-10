#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <string>
#include <regex>

const unsigned short HTTP_DEFAULT_PORT = 80;
const unsigned short HTTPS_DEFAULT_PORT = 443;
const unsigned short MAX_PORT = 65535;
const unsigned short MIN_PORT = 0;

CHttpUrl::CHttpUrl(std::string const& url)
{
    std::regex ex("([^ #?]*)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)");
    std::cmatch match;

    if (!regex_match(url.c_str(), match, ex))
    {
        throw CUrlParsingError("Url parsing error");
    }
    
    m_protocol = GetProtocol(match[1]);
    m_domain = match[2];
    m_port = GetPort(match[3], m_protocol);
    m_document = match[4];
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
    : CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
    if (domain.empty())
    {
        throw std::invalid_argument("Invalid domain");
    }

    m_domain = domain;
    m_document = CHttpUrl::GetDocument(document);
    m_protocol = protocol;    
    m_port = port;
}

Protocol CHttpUrl::GetProtocol(std::string protocolStr) const
{
    std::transform(protocolStr.begin(), protocolStr.end(), protocolStr.begin(), tolower);

    if (protocolStr == "http")
    {
        return(Protocol::HTTP);
    }
    
    if (protocolStr == "https")
    {
        return(Protocol::HTTPS);
    }
    
    throw std::invalid_argument("Invalid protocol");
}

bool IsNumber(const std::string& line)
{
    for (char ch : line)
    {
        if (!isascii(ch) || !isdigit(ch))
        {
            return false;
        }
    }
    return true;
}

unsigned short CHttpUrl::GetPort(const std::string& portStr, const Protocol& protocol) const
{
    if (portStr.empty())
    {
        return(GetDefaultPort(protocol));
    }
    
    if (!IsNumber(portStr))
    {
        throw std::invalid_argument("Invalid port");
    }
    
    int port = std::stoi(portStr.c_str());
    if (!(port >= MIN_PORT && port <= MAX_PORT))
    {
        throw std::invalid_argument("Invalid port");
    }
    
    return port;
}

unsigned short CHttpUrl::GetDefaultPort(const Protocol& protocol) const
{
    switch (protocol)
    {
    case Protocol::HTTP:
        return HTTP_DEFAULT_PORT;
    case Protocol::HTTPS:
        return HTTPS_DEFAULT_PORT;
    }

    return 0;
}

std::string CHttpUrl::GetDocument(const std::string& document) const
{
    if (document.empty() || document[0] != '/')
    {
        return '/' + document;
    }
    return document;
}

std::string ConvertProtocolToString(const Protocol& protocol)
{
    switch (protocol)
    {
    case Protocol::HTTP:
        return "http";
    case Protocol::HTTPS:
        return "https";
    }

    return "";
}

std::string CHttpUrl::GetURL() const
{
    if (m_port == HTTP_DEFAULT_PORT || m_port == HTTPS_DEFAULT_PORT)
    {
        return ConvertProtocolToString(m_protocol) + "://" + m_domain + m_document;
    }
 
    return ConvertProtocolToString(m_protocol) + "://" + m_domain + ":" + std::to_string(m_port) + m_document;
}

std::string CHttpUrl::GetDomain() const
{
    return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
    return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
    return m_protocol;
}

std::string CHttpUrl::GetProtocolStr() const
{
    return ConvertProtocolToString(m_protocol);
}

unsigned short CHttpUrl::GetPort() const
{
    return m_port;
}
