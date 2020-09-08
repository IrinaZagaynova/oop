#include "stdafx.h"
#include "MyString.h"
#include <algorithm>

CMyString::CMyString()
{
	m_length = 0;
	m_pString = new char[1];
	m_pString[0] = '\0';
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{	
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	m_pString = new char[m_length + 1];
	memcpy(m_pString, pString, m_length);
	m_pString[m_length] = '\0';
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_pString, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: CMyString(other)
{
	other.m_length = 0;
	other.m_pString = new char[1];
	other.m_pString[0] = '\0';
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	delete[] m_pString;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_pString;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		return "";
	}
	
	if (start + length > m_length)
	{
		length = m_length - start;
	}
	
	return(CMyString(m_pString + start, length));
}

void CMyString::Clear()
{
	delete[] m_pString; 
	m_length = 0;
	m_pString = new char[1];
	m_pString[0] = '\0';
}

CMyString const CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString tmp(other);
		std::swap(m_pString, tmp.m_pString);
		std::swap(m_length, tmp.m_length);
	}

	return *this;
}

CMyString const CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		delete[] m_pString;
		m_length = other.m_length;
		m_pString = other.m_pString;

		other.m_length = 0;
		other.m_pString = new char[1];
		other.m_pString[0] = '\0';
	}
	
	return *this;
}

CMyString const operator+(const CMyString& str1, const CMyString& str2)
{
	CMyString result;
	result.m_length = str1.GetLength() + str2.GetLength();
	result.m_pString = new char[result.m_length + 1];

	memcpy(result.m_pString, str1.m_pString, str1.m_length);
	memcpy(result.m_pString + str1.m_length, str2.m_pString, str2.m_length);
	result.m_pString[result.m_length] = '\0';

	return result;
}

CMyString& CMyString::operator+=(const CMyString& str2)
{
	*this = *this + str2;
	return *this;
}

bool CMyString::operator==(const CMyString& other) const
{
	return (m_length == other.m_length && strcmp(m_pString, other.m_pString) == 0);
}

bool CMyString::operator!=(const CMyString& other) const
{
	return !(*this == other);
}

bool CMyString::operator<(const CMyString& other) const
{
	size_t minLength = std::min(m_length, other.GetLength());
	for (size_t i = 0; i < minLength; i++)
	{
		if (this->m_pString[i] < other.m_pString[i])
		{
			return true;
		}
	}

	if (m_length < other.GetLength())
	{
		return true;
	}
	
	return false;
}

bool CMyString::operator>(const CMyString& other) const
{
	return (!(*this < other) && *this != other);
}

bool CMyString::operator<=(const CMyString& other) const
{
	return (*this < other || *this == other);
}

bool CMyString::operator>=(const CMyString& other) const
{
	return (*this > other || *this == other);
}

char const CMyString::operator[](size_t position) const
{
	return m_pString[position];
}

char& CMyString::operator[](size_t position)
{
	return m_pString[position];
}

std::ostream& operator<<(std::ostream& stream, CMyString const& str)
{
	for (size_t i = 0; i < str.GetLength(); i++)
	{
		stream << str[i];
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& str)
{
	std::string input;
	stream >> input;
	str = CMyString(input);
	return stream;
}