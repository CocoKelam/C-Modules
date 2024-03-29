#pragma once
#include <string>

class StrCodeUtil
{
public:
	StrCodeUtil();
	~StrCodeUtil();


	static std::string  UnicodeToUTF8(const std::wstring& wstr);

	static std::wstring UTF8ToUnicode(const std::string & str);

	static std::string  UnicodeToANSI(const std::wstring & wstr);

	static std::wstring ANSIToUnicode(const std::string & str);

	static std::string  UTF8ToANSI(const std::string & str);

	static std::string  ANSIToUTF8(const std::string & str);
};

