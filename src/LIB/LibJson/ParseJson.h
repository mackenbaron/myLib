#pragma once
class ParseJson
{
public:
	ParseJson(void);
	~ParseJson(void);



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

