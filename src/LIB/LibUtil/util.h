#ifndef UTIL_H
#define UTIL_H

class util
{
public:

	void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // 把UTF-8转换成Unicode
	void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode 转换成UTF-8
	void UnicodeToGB2312(char* pOut,wchar_t uData);  // 把Unicode 转换成 GB2312
	void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成　Unicode
	void GB2312ToUTF_8(std::string& pOut,char *pText, int pLen);//GB2312 转为 UTF-8
	void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);//UTF-8 转为 GB2312
	WCHAR* AnsiToUnicode( const char* szStr );//char to wchar
	char* UnicodeToAnsi( const WCHAR* szStr );//wchar to char
	char* UnicodeToUTF8( const WCHAR* szStr );//wchar to utf8
	wchar_t* Utf8ToUnicode(const char* utf);//utf8 to wchar
	char* intTOStirng(const int n);
	char* DoubleTOString(const double n);
	int StringToInt(const char* src);
	double StringTODouble(const char* src);
	
};

#endif // UTIL_H
