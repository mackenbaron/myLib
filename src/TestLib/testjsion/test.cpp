#pragma once
#include "stdafx.h"
#include "rapidjson/reader.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/error/en.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <string>
using namespace rapidjson;
using namespace std;

struct MyHandler {
	bool Null()
	{ 
		cout << "Null()" << endl;
		return true; 
	}
	bool Bool(bool b) 
	{ 
		cout << "Bool(" << boolalpha << b << ")" << endl; 
		return true; 
	}
	bool Int(int i) 
	{ 
		cout << "Int(" << i << ")" << endl; 
		return true; 
	}
	bool Uint(unsigned u) 
	{ 
		cout << "Uint(" << u << ")" << endl;
		return true;
	}
	bool Int64(int64_t i) 
	{ 
		cout << "Int64(" << i << ")" << endl;
		return true; 
	}
	bool Uint64(uint64_t u) 
	{ 
		cout << "Uint64(" << u << ")" << endl;
		return true; 
	}
	bool Double(double d) 
	{ 
		cout << "Double(" << d << ")" << endl;
		return true;
	}
	bool String(const char* str, SizeType length, bool copy) 
	{ 
		_tempsrc.append(str);
		_tempsrc.append(",");
		cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
		return true;
	}
	bool StartObject() 
	{ 
		_tempsrc += "StartObject";
		cout << "StartObject()" << endl; 
		return true; 
	}
	bool Key(const char* str, SizeType length, bool copy) 
	{
		_tempsrc.append(str);
		_tempsrc.append(",");
		cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
		return true;
	}
	bool EndObject(SizeType memberCount) 
	{ 
		cout << "EndObject(" << memberCount << ")" << endl;
		return true; 
	}
	bool StartArray() 
	{
		cout << "StartArray()" << endl; 
		return true; 
	}
	bool EndArray(SizeType elementCount)
	{ 
		cout << "EndArray(" << elementCount << ")" << endl;
		return true; 
	}
public:
	std::string _tempsrc;
};
int main()
{
	const char json[] = "{\"hello\":\"world\",\"t\":true,\"f\":false,\"n\":null,\"i\":123,\"pi\":3.1416,\"a\":[{\"a\":0},{\"a\":1},{\"a\":2},{\"a\":3}]}";
 
 	MyHandler handler;
 	Reader reader;
 	StringStream ss(json);
 	reader.Parse(ss, handler);
 
 	return 0;
	//StringBuffer s;
// 	Writer<StringBuffer> writer(s);
// 
// 	writer.StartObject();
// 	writer.String("hello");
// 	writer.String("world");
// 	writer.String("t");
// 	writer.Bool(true);
// 	writer.String("f");
// 	writer.Bool(false);
// 	writer.String("n");
// 	writer.Null();
// 	writer.String("i");
// 	writer.Uint(123);
// 	writer.String("pi");
// 	writer.Double(3.1416);
// 	writer.String("a");
// 	writer.StartArray();
// 	for (unsigned i = 0; i < 4; i++)
// 	{
// 		writer.StartObject();
// 		writer.String("a");
// 		writer.Uint(i);
// 		writer.EndObject();
// 	}
// 	writer.EndArray();
// 	writer.EndObject();
// 
// 	cout << s.GetString() << endl;
// 
// 	return 0;
}