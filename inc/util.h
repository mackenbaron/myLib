#ifndef UTIL_H
#define UTIL_H

class util
	{
	public:
#ifdef WIN32
		void readINIFileString(std::string path,std::string root,std::string userkey,std::string &uservalue,std::string def);
		void readINIFileInt(std::string path,std::string root,std::string userkey,int &userValue,int def);
		void writeINIFileString(std::string path,std::string root,std::string userkey,std::string value);
#endif
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
		std::vector<std::string> split(std::string &str,std::string &pattern);
		std::string GBKToUTF8(const std::string& strGBK); 
		std::string UTF8ToGBK(const std::string& strUTF8);
		void ReplaceSrc(std::string&s1,const std::string&s2,const std::string&s3);
		std::string Base64Encode(const unsigned char* Data,int DataByte);
		std::string Base64Decode(const char* Data,int DataByte,int& OutByte);

};



#endif // UTIL_H
