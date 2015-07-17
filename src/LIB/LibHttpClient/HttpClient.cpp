#include "StdAfx.h"
#include "HttpClient.h"
#include "WinHttpClient.h"
#include "util.h"


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
	util u;
	// Set URL.
	WinHttpClient client(u.AnsiToUnicode(url.c_str()));

	if(!UserAgent.empty())
	{
		 client.SetUserAgent(u.AnsiToUnicode(UserAgent.c_str()));
	}
	if(!Proxy.empty())
	{
		client.SetProxy(u.AnsiToUnicode(Proxy.c_str()));
	}
	if(!Cookies.empty())
	{
		 client.SetAdditionalRequestCookies(u.AnsiToUnicode(Cookies.c_str()));
	}
	// Send http request, a GET request by default.
	client.SendHttpRequest();

	// The response header.
	wstring httpResponseHeader = client.GetResponseHeader();
	ResponseHeader = u.UnicodeToAnsi(httpResponseHeader.c_str());
	// The response content.
	wstring httpResponseContent = client.GetResponseContent();
	ResponseContent = u.UnicodeToAnsi(httpResponseContent.c_str());
	return _wtoi(client.GetResponseStatusCode().c_str());
}

int HttpClient::clientPost(IN std::string url,IN std::string contentData,
	OUT std::string &ResponseHeader,OUT std::string &ResponseContent,
	IN std::string UserAgent/*=""*/,IN std::string Proxy/*=""*/,IN std::string Cookies/*=""*/)
{
	util u;
	WinHttpClient client(u.AnsiToUnicode(url.c_str()));

	// Set post data.
	string data = contentData;
	if(!contentData.empty())
	{
		client.SetAdditionalDataToSend((BYTE *)data.c_str(), data.size());
	}
	if(!UserAgent.empty())
	{
		client.SetUserAgent(u.AnsiToUnicode(UserAgent.c_str()));
	}
	if(!Proxy.empty())
	{
		client.SetProxy(u.AnsiToUnicode(Proxy.c_str()));
	}
	if(!Cookies.empty())
	{
		client.SetAdditionalRequestCookies(u.AnsiToUnicode(Cookies.c_str()));
	}
	// Set request headers.
	wchar_t szSize[50] = L"";
	swprintf_s(szSize, L"%d", data.size());
	wstring headers = L"Content-Length: ";
	headers += szSize;
	headers += L"\r\nContent-Type: application/x-www-form-urlencoded\r\n";
	client.SetAdditionalRequestHeaders(headers);

	// Send http post request.
	client.SendHttpRequest(L"POST");

	wstring httpResponseHeader = client.GetResponseHeader();
	wstring httpResponseContent = client.GetResponseContent();

	ResponseHeader = u.UnicodeToAnsi(httpResponseHeader.c_str());
	ResponseContent = u.UnicodeToAnsi(httpResponseContent.c_str());
	return _wtoi(client.GetResponseStatusCode().c_str());
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
