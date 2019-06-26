#include "stdafx.h"
#include "StrCodeUtil.h"
#include <codecvt> 
#include <memory>

StrCodeUtil::StrCodeUtil()
{
}


StrCodeUtil::~StrCodeUtil()
{
}


std::string StrCodeUtil::UnicodeToUTF8(const std::wstring& wstr)
{

	std::string ret;
	try 
	{
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.to_bytes(wstr);
	}
	catch (const std::exception& e) 
	{
		return ret;
	}
	return ret;

}

std::wstring StrCodeUtil::UTF8ToUnicode(const std::string & str)
{

	std::wstring ret;
	try
	{
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.from_bytes(str);
	}
	catch (const std::exception & e) 
	{
		std::string strTem = e.what();
		
		int a =0 ;

	}
	return ret;
}

std::string StrCodeUtil::UnicodeToANSI(const std::wstring & wstr)
{
	setlocale(LC_CTYPE, "");
	std::string ret;
	std::mbstate_t state = {};
	const wchar_t *src = wstr.data();
	size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) 
	{
		std::unique_ptr< char[] > buff(new char[len + 1]);
		len = std::wcsrtombs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len)
		{
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}

std::wstring StrCodeUtil::ANSIToUnicode(const std::string & str)
{
	setlocale(LC_CTYPE, "");
	std::wstring ret;
	std::mbstate_t state = {};
	const char *src = str.data();
	size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) 
	{
		std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
		len = std::mbsrtowcs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) 
		{
			ret.assign(buff.get(), len);
		}
	}
	return ret;

}

std::string StrCodeUtil::UTF8ToANSI(const std::string & str)
{

	return UnicodeToANSI(UTF8ToUnicode(str));

}

std::string StrCodeUtil::ANSIToUTF8(const std::string & str)
{
	return UnicodeToUTF8(ANSIToUnicode(str));
}
