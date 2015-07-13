#include "StdAfx.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "ParseJson.h"
#include "util.h"
#include <iostream>

using namespace rapidjson;
using namespace std;

StringBuffer s;
Writer<StringBuffer> writer(s);
ParseJson::ParseJson(void)
{
	s.Clear();
	writer.Reset(s);
}


ParseJson::~ParseJson(void)
{
}


int ParseJson::WriteJsonStart()
{
	s.Clear();
	writer.Reset(s);
	writer.StartObject();
	return 0;
}

std::string  ParseJson::WriteJsonEnd()
{
	writer.EndObject();
	return s.GetString();
}

int ParseJson::WriteJsonArrayStart()
{
	 writer.StartArray();
	 return 0;
}

int ParseJson::WriteJsonArrayEnd()
{
	writer.EndArray();
	return 0;
}

int ParseJson::WriteJsonInt(std::string Keysrc,int value)
{
	writer.String(Keysrc.c_str());
	writer.Int(value);
	return 0;
}

int ParseJson::WriteJsonDoulbe(std::string KeySrc,double value)
{
	writer.String(KeySrc.c_str());
	writer.Double(value);
	return 0;
}

int ParseJson::WriteJsonString(std::string Keysrc,std::string value)
{
	writer.String(Keysrc.c_str());
	writer.String(value.c_str());
	return 0;
}

int ParseJson::WriteJsonWstring(std::string Keysrc,std::wstring value)
{
	writer.String(Keysrc.c_str());
	writer.String(util::UnicodeToAnsi(value.c_str()));
	return 0;
}

int ParseJson::WriteJsonBool(std::string Keysrc,bool value)
{
	writer.String(Keysrc.c_str());
	writer.Bool(value);
	return 0;
}

int ParseJson::WriteJsonValueNULL(std::string Keysrc)
{
	writer.String(Keysrc.c_str());
	writer.Null();
	return 0;
}
