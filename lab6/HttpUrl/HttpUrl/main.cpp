#include <iostream>
#include <string>
#include "HttpUrl.h"

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{ 
		try
		{
			CHttpUrl url("domain.com", "index.html", Protocol::HTTPS, 65536);
			std::cout << "protocol - " << url.GetProtocol() << "\n"
				<< "domain - " << url.GetDomain() << "\n"
				<< "document - " << url.GetDocument() << "\n"
				<< "port - " << url.GetPort() << "\n"
				<< "url - " << url.GetURL() << "\n";
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what() << "\n";
		}
	}

	return 0;
}