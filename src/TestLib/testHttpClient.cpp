// testHttpClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HttpClient.h"

int _tmain(int argc, _TCHAR* argv[])
{
	HttpClient hc;
	std::string url = "http://192.168.1.31:8080/update";
	std::string date ="a=2&b=4&x=3";
	std::string rc="";
	std::string rs="";

	int x = hc.clinetPost(url,date,rc,rs);

	return 0;
}

