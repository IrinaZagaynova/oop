#pragma once
#include "stdafx.h"

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(const std::string& stlString);
	~CMyString();
	size_t GetLength()const;
	const char* GetStringData()const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX)const;
	void Clear();

	CMyString const operator =(const CMyString& other);
	CMyString const operator =(CMyString&& other) noexcept;

	friend CMyString const operator +(const CMyString& str1, const CMyString& str2);

	CMyString& operator +=(CMyString const& str2);

	bool operator ==(const CMyString& other)const;
	bool operator !=(const CMyString& other)const;
	bool operator <(const CMyString& other)const;
	bool operator >(const CMyString& other)const;
	bool operator <=(const CMyString& other)const;
	bool operator >=(const CMyString& other)const;

	char const operator [](size_t position)const;
	char& operator [](size_t position);
private:
	char* m_pString;
	size_t m_length;
};

std::ostream& operator <<(std::ostream& stream, CMyString const& str);
std::istream& operator >>(std::istream& stream, CMyString& str);