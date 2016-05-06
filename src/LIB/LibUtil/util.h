#ifndef UTIL_H
#define UTIL_H

class util
{
	public:
		void readINIFileString(std::string path,std::string root,std::string userkey,std::string &uservalue,std::string def);
		void readINIFileInt(std::string path,std::string root,std::string userkey,int &userValue,int def);
		void writeINIFileString(std::string path,std::string root,std::string userkey,std::string value);
		void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // ��UTF-8ת����Unicode
		void UnicodeToUTF_8(char* pOut,wchar_t* pText);  //Unicode ת����UTF-8
		void UnicodeToGB2312(char* pOut,wchar_t uData);  // ��Unicode ת���� GB2312
		void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// GB2312 ת���ɡ�Unicode
		void GB2312ToUTF_8(std::string& pOut,char *pText, int pLen);//GB2312 תΪ UTF-8
		void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);//UTF-8 תΪ GB2312
		std::string intTOStirng(const int n);//int to char
		std::string DoubleTOString(const double n);//double to char
		int StringToInt(const char* src); //char to int
		double StringTODouble(const char* src);// char to double
		std::vector<std::string> split(std::string &str,std::string &pattern);//ȡ�ָ���֮��Ķ���ַ�
		std::string GBKToUTF8(const std::string& strGBK); //gbk to utf8
		std::string UTF8ToGBK(const std::string& strUTF8);//utf8 to gbk
		void ReplaceSrc(std::string&s1,const std::string&s2,const std::string&s3);//��ѯ�滻�ַ���
		std::string Base64Encode(const unsigned char* Data,int DataByte);//����base64
		std::string Base64Decode(const char* Data,int DataByte,int& OutByte);//����base64
		std::string UrlEncode(const std::string& szToEncode);//����url ����
		std::string UrlDecode(const std::string& szToDecode);//����url ����
		bool CheckFormatJson(std::string src);//��֤json�Ƿ�Ϸ�
		std::string U2A(const std::wstring& str);//Unicode�ַ�תAscii�ַ�
		std::wstring A2U(const std::string& str);//Ascii�ַ�תUnicode
		std::string U2Utf(const std::wstring& wstrUnicode);//Unicodeתutf8 
		std::wstring Utf2U(const std::string &str);//utf8תUnicode 		 
		bool SplitStringW(const std::wstring& strSource,const std::wstring& strFlag, std::vector<std::wstring>& paramList);//�ָ��ַ���	
		bool SplitStringA(const std::string& strSource,const std::string& strFlag, std::vector<std::string>& paramList);//�ָ��ַ���
		std::wstring StrReplaceW(const std::wstring& strContent, const std::wstring& strTag, const std::wstring& strReplace);//�滻�ַ���  
		std::string StrReplaceA( const std::string& strContent, const std::string& strTag, const std::string& strReplace );//�滻�ַ��� 

		int ReadFileDate(std::string filePaht,std::string &message);//���ļ�
		int WriteFileDate(std::string filename,unsigned char* date,int len);//д�ļ�
};



#endif // UTIL_H
