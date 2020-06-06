#include "stdafx.h"
#include "../HttpUrl/HttpUrl.h"
#include "../HttpUrl/UrlParsingError.h"

template <typename Ex, typename Fn>
void ExpectException(Fn&& fn, const std::string& expectedDescription)
{
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		return e.what() == expectedDescription;
	});
}

template <typename Ex>
void ExpectConstructorFailure(const std::string& url, const std::string& expectedDescription)
{
	ExpectException<Ex>([&]{
		CHttpUrl url(url);
	}, expectedDescription);
}

template <typename Ex>
void ExpectConstructorFailure(
	const std::string& domain, 
	const std::string& document,
	const Protocol& protocol, 
	const std::string& expectedDescription)
{
	ExpectException<Ex>([&] {
		CHttpUrl url(domain, document, protocol);
		}, expectedDescription);
}

template <typename Ex>
void ExpectConstructorFailure(
	const std::string& domain, 
	const std::string& document, 
	const Protocol& protocol, 
	unsigned short port, 
	const std::string& expectedDescription)
{
	ExpectException<Ex>([&] {
		CHttpUrl url(domain, document, protocol, port);
		}, expectedDescription);
}

void VerifyHttpUrlParams(
	CHttpUrl url,
	const std::string& expectedDomain,
	const std::string& expectedDocument,
	Protocol expectedProtocol,
	unsigned short expectedPort)
{
	BOOST_CHECK_EQUAL(url.GetDomain(), expectedDomain);
	BOOST_CHECK_EQUAL(url.GetDocument(), expectedDocument);
	BOOST_CHECK_EQUAL(url.GetProtocol(), expectedProtocol);
	BOOST_CHECK_EQUAL(url.GetPort(), expectedPort);
}

BOOST_AUTO_TEST_SUITE(HttpUrl)
	BOOST_AUTO_TEST_CASE(constructor_can_parse_url)
	{
		CHttpUrl url("https://domain.com:65535/index.html");
		VerifyHttpUrlParams(url, "domain.com", "/index.html", Protocol::HTTPS, 65535);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://domain.com:65535/index.html");
	
		CHttpUrl url2("http://domain.com/index.html");
		VerifyHttpUrlParams(url2, "domain.com", "/index.html", Protocol::HTTP, 80);
		BOOST_CHECK_EQUAL(url2.GetURL(), "http://domain.com/index.html");

		CHttpUrl url3("https://domain.com/index.html");
		VerifyHttpUrlParams(url3, "domain.com", "/index.html", Protocol::HTTPS, 443);
		BOOST_CHECK_EQUAL(url3.GetURL(), "https://domain.com/index.html");
	}

	BOOST_AUTO_TEST_CASE(throws_an_exception_if_url_cant_be_parsed)
	{
		ExpectConstructorFailure<CUrlParsingError>("domain.com", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("https://", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("https//domain.com", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("https:///domain.com", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("https://:123", "Url parsing error");
	}

	BOOST_AUTO_TEST_CASE(constructor_can_initialize_url_params_by_domain_documentand_and_protocol)
	{
		CHttpUrl url("domain.com", "/index.html");
		VerifyHttpUrlParams(url, "domain.com", "/index.html", Protocol::HTTP, 80);
		BOOST_CHECK_EQUAL(url.GetURL(), "http://domain.com/index.html");

		CHttpUrl url2("domain.com", "/index.html", Protocol::HTTP);
		VerifyHttpUrlParams(url2, "domain.com", "/index.html", Protocol::HTTP, 80);
		BOOST_CHECK_EQUAL(url2.GetURL(), "http://domain.com/index.html");

		CHttpUrl url3("domain.com", "index.html", Protocol::HTTPS);
		VerifyHttpUrlParams(url3, "domain.com", "/index.html", Protocol::HTTPS, 443);
		BOOST_CHECK_EQUAL(url3.GetURL(), "https://domain.com/index.html");
	}

	BOOST_AUTO_TEST_CASE(constructor_that_initializes_url_params_by_domain_document_protocol_and_port)
	{
		CHttpUrl url("domain.com", "index.html", Protocol::HTTPS, 1);
		VerifyHttpUrlParams(url, "domain.com", "/index.html", Protocol::HTTPS, 1);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://domain.com:1/index.html");

		CHttpUrl url2("domain.com", "index.html", Protocol::HTTP, 80);
		VerifyHttpUrlParams(url2, "domain.com", "/index.html", Protocol::HTTP, 80);
		BOOST_CHECK_EQUAL(url2.GetURL(), "http://domain.com/index.html");

		CHttpUrl url3("domain.com", "/index.html", Protocol::HTTPS, 443);
		VerifyHttpUrlParams(url3, "domain.com", "/index.html", Protocol::HTTPS, 443);
		BOOST_CHECK_EQUAL(url3.GetURL(), "https://domain.com/index.html");
	}

	BOOST_AUTO_TEST_CASE(if_the_protocol_is_incorrect_throws_an_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("protocol://domain.com", "Invalid protocol");
	}

	BOOST_AUTO_TEST_CASE(if_the_domain_is_empty_throws_an_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("", "index.html", Protocol::HTTPS, "Invalid domain");
		ExpectConstructorFailure<std::invalid_argument>("", "index.html", Protocol::HTTPS, 1, "Invalid domain");
	}

	BOOST_AUTO_TEST_CASE(if_the_port_is_incorrect_throws_an_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("https://domain.com:a", "Invalid port");
		ExpectConstructorFailure<std::invalid_argument>("https://domain.com:65536", "Invalid port");
		ExpectConstructorFailure<std::invalid_argument>("https://domain.com.com:-1", "Invalid port");
		ExpectConstructorFailure< std::invalid_argument>("domain.com", "index.html", Protocol::HTTPS, 0, "Invalid port");
	}

BOOST_AUTO_TEST_SUITE_END()