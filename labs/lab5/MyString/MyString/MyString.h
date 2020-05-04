#pragma once
#include <string>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other);
	CMyString(std::string const& stlString);
	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString& operator=(const CMyString& other);
	CMyString& operator=(CMyString&& other);
	CMyString const friend operator+(const CMyString& str1, const CMyString& str2);
	CMyString& operator+=(const CMyString& other);

	bool friend operator==(const CMyString& str1, const CMyString& str2);
	bool friend operator!=(const CMyString& str1, const CMyString& str2);
	bool friend operator<(const CMyString& str1, const CMyString& str2);
	bool friend operator>(const CMyString& str1, const CMyString& str2);
	bool friend operator<=(const CMyString& str1, const CMyString& str2);
	bool friend operator>=(const CMyString& str1, const CMyString& str2);

	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	std::ostream friend& operator<<(std::ostream& stream, const CMyString& str);
	std::istream friend& operator>>(std::istream& stream, CMyString& str);

private:
	char* m_pString;
	size_t m_length;
};
