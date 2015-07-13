#pragma once
class ParseJson
{
public:
	ParseJson(void);
	~ParseJson(void);

	int ReadJsonInt(std::string & jsonSrc,std::string Keysrc);
	double ReadJsonDouble(std::string & jsonSrc,std::string Keysrc);
	std::string ReadJsonString(std::string &jsonSrc,std::string keysrc);
	std::wstring ReadJsonWString(std::string &jsonSrc,std::string keysrc);
	bool ReadJsonBool(std::string &jsonSrc,std::string keysrc);

	std::string UpdateJsonInt(std::string &jsonSrc,std::string KeySrc,int uvalue);
	std::string UpdateJsonDouble(std::string &jsonSrc,std::string KeySrc,double uvalue);
	std::string UpdateJsonString(std::string &jsonSrc,std::string KeySrc,std::string uvalue);
	std::string UpdateJsonWString(std::string &jsonSrc,std::string KeySrc,std::wstring uvalue);
	std::string UpdateJsonBool(std::string &jsonSrc,std::string KeySrc,bool uvalue);

	int WriteJsonStart();
	std::string  WriteJsonEnd();
	int WriteJsonArrayStart();
	int WriteJsonArrayEnd();
	int WriteJsonInt(std::string Keysrc,int value);
	int WriteJsonDoulbe(std::string KeySrc,double value);
	int WriteJsonString(std::string Keysrc,std::string value);
	int WriteJsonWstring(std::string Keysrc,std::wstring value);
	int WriteJsonBool(std::string Keysrc,bool value);
	int WriteJsonValueNULL(std::string Keysrc);
};

