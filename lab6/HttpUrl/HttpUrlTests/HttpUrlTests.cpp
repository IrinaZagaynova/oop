#include "stdafx.h"
#include "../HttpUrl/HttpUrl.h"
#include "../HttpUrl/UrlParsingError.h"

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

BOOST_AUTO_TEST_SUITE(tests_of_the_constructor_which_pars_url)
	
	BOOST_AUTO_TEST_CASE(constructor_can_parse_url_with_protocol_and_domain)
	{
		CHttpUrl url("https://example.com");
		VerifyHttpUrlParams(url, "example.com", "", Protocol::HTTPS, 443);
	}
	
	BOOST_AUTO_TEST_CASE(constructor_can_parse_url_with_protocol_domain_and_document)
	{
		CHttpUrl url("https://example.com/index.html");
		VerifyHttpUrlParams(url, "example.com", "/index.html", Protocol::HTTPS, 443);
	}

	BOOST_AUTO_TEST_CASE(constructor_can_parse_url_with_protocol_domain_document_and_port)
	{
		CHttpUrl url("https://example.com:65535/index.html");
		VerifyHttpUrlParams(url, "example.com", "/index.html", Protocol::HTTPS, 65535);
	}

	BOOST_AUTO_TEST_CASE(if_url_cant_be_parsed_throws_an_exception)
	{
		ExpectConstructorFailure<CUrlParsingError>("", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("example.com", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("https://", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("https//example.com", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("https:///example.com", "Url parsing error");
		ExpectConstructorFailure<CUrlParsingError>("https://:123", "Url parsing error");
	}

	BOOST_AUTO_TEST_CASE(if_the_protocol_is_incorrect_throws_an_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("protocol://example.com", "Invalid protocol");
	}

	BOOST_AUTO_TEST_CASE(if_the_port_is_incorrect_throws_an_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("https://example.com:a", "Invalid port");
		ExpectConstructorFailure<std::invalid_argument>("https://example.com:65536", "Invalid port");
		ExpectConstructorFailure<std::invalid_argument>("https://example.com.com:-1", "Invalid port");
	}

BOOST_AUTO_TEST_SUITE_END()

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

BOOST_AUTO_TEST_SUITE(tests_of_the_constructor_that_gets_protocol_domain_and_document)

	BOOST_AUTO_TEST_CASE(constructor_can_initialize_url_params_by_domain_document_and_protocol)
	{
		CHttpUrl url("example.com", "/index.html", Protocol::HTTP);
		VerifyHttpUrlParams(url, "example.com", "/index.html", Protocol::HTTP, 80);

		CHttpUrl url2("example.com", "index.html", Protocol::HTTPS);
		VerifyHttpUrlParams(url2, "example.com", "/index.html", Protocol::HTTPS, 443);
	}

	BOOST_AUTO_TEST_CASE(if_the_protocol_isnt_entered_the_default_protocol_is_http)
	{
		CHttpUrl url("example.com", "/index.html");
		VerifyHttpUrlParams(url, "example.com", "/index.html", Protocol::HTTP, 80);
	}

	BOOST_AUTO_TEST_CASE(if_the_domain_is_empty_throws_an_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("", "index.html", Protocol::HTTPS, "Invalid domain");
	}

BOOST_AUTO_TEST_SUITE_END()

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

BOOST_AUTO_TEST_SUITE(tests_of_the_constructor_that_gets_protocol_domain_document_and_port)	
	
	BOOST_AUTO_TEST_CASE(constructor_can_initialize_url_params_by_domain_document_protocol_and_port)
	{
		CHttpUrl url("example.com", "/index.html", Protocol::HTTP, 65534);
		VerifyHttpUrlParams(url, "example.com", "/index.html", Protocol::HTTP, 65534);
	}

	BOOST_AUTO_TEST_CASE(if_the_domain_is_empty_throws_an_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("", "index.html", Protocol::HTTPS, 100, "Invalid domain");
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(GetUrl_tests)

	BOOST_AUTO_TEST_CASE(should_return_url)
	{
		CHttpUrl url("https://example.com:100/index.html");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://example.com:100/index.html");
	}

	BOOST_AUTO_TEST_CASE(should_return_url_without_document_and_port)
	{
		CHttpUrl url("https://example.com");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://example.com");
	}

	BOOST_AUTO_TEST_CASE(should_return_url_without_port)
	{
		CHttpUrl url("https://example.com/index.html");
		BOOST_CHECK_EQUAL(url.GetURL(), "https://example.com/index.html");

		CHttpUrl url1("http://example.com:80/index.html");
		BOOST_CHECK_EQUAL(url1.GetURL(), "http://example.com/index.html");

		CHttpUrl url2("https://example.com:443/index.html");
		BOOST_CHECK_EQUAL(url2.GetURL(), "https://example.com/index.html");
	}

BOOST_AUTO_TEST_SUITE_END()