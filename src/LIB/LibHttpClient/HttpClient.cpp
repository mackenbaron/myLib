#include "StdAfx.h"
#include "HttpClient.h"
#include "WinHttpClient.h"
#include "util.h"
#include "SocketRequestClass.h"


HttpClient::HttpClient(void)
{
}


HttpClient::~HttpClient(void)
{
}

int HttpClient::clientGet(IN std::string url,
	OUT std::string &ResponseHeader,OUT std::string &ResponseContent,
	IN std::string UserAgent/*=""*/,IN std::string Proxy/*=""*/,IN std::string Cookies/*=""*/)
{
	SocketRequest mSocketRequest;
	
	int r = mSocketRequest.setRequestGetRequest(const_cast<char*>(url.c_str()),ResponseContent,ResponseHeader);
	return r;
}

int HttpClient::clientPost(IN std::string url,IN std::string contentData,
	OUT std::string &ResponseHeader,OUT std::string &ResponseContent,
	IN std::string UserAgent/*=""*/,IN std::string Proxy/*=""*/,IN std::string Cookies/*=""*/)
{
	SocketRequest mSocketRequest;
	int r = mSocketRequest.setRequestPostRequest(const_cast<char*>(url.c_str()),const_cast<char*>(contentData.c_str()),ResponseContent,ResponseHeader);
	return r;	
}

int HttpClient::ClientDownload(IN std::string sourSrc,IN std::string destSrc,IN std::string Cookies)
{
	util u;
	WinHttpClient downloadClient(u.AnsiToUnicode(sourSrc.c_str()));
	downloadClient.SetUserAgent(L"Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; InfoPath.2; CIBA; MS-RTC LM 8)");
	downloadClient.SetAdditionalRequestCookies(u.AnsiToUnicode(Cookies.c_str()));
	if (!downloadClient.SendHttpRequest())
	{
		return -1;
	}
	downloadClient.SaveResponseToFile(u.AnsiToUnicode(destSrc.c_str()));
	return 0;
}
