#ifndef UTIL_H
#define UTIL_H

class util
	{
	public:
#ifdef WIN32
		static void readINIFileString(std::string path,std::string root,std::string userkey,std::string &uservalue,std::string def);
		static void readINIFileInt(std::string path,std::string root,std::string userkey,int &userValue,int def);
		static void writeINIFileString(std::string path,std::string root,std::string userkey,std::string value);
#endif
		static void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // 把UTF-8转换成Unicode
		static void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode 转换成UTF-8
		static void UnicodeToGB2312(char* pOut,wchar_t uData);  // 把Unicode 转换成 GB2312
		static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 转换成　Unicode
		static void GB2312ToUTF_8(std::string& pOut,char *pText, int pLen);//GB2312 转为 UTF-8
		static void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);//UTF-8 转为 GB2312
		static WCHAR* AnsiToUnicode( const char* szStr );//char to wchar
		static char* UnicodeToAnsi( const WCHAR* szStr );//wchar to char
		static char* UnicodeToUTF8( const WCHAR* szStr );//wchar to utf8
		static wchar_t* Utf8ToUnicode(const char* utf);//utf8 to wchar
		static char* intTOStirng(const int n);
		static char* DoubleTOString(const double n);
		static int StringToInt(const char* src);
		static double StringTODouble(const char* src);

};



#endif // UTIL_H
