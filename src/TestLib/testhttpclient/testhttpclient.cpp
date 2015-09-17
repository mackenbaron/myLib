// testhttpclient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HttpClient.h"

int main(int argc, char* argv[])
{
	std::string url="http://220.181.112.244:80/index.html";///"http://192.168.0.160:8089/Engine/EngInfo";
	//std::string pro="";
	//pro="TaskID=123456&DevID=123456&State=0&Message=4165412";

	HttpClient cl;
	std::string _tempa="";
	std::string _tempb ="";
	cl.clientGet(url,_tempa,_tempb);

	return 0;
}

