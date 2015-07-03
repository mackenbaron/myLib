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

int HttpClient::clientGet(IN std::string url,OUT std::string &ResponseHeader,OUT std::string &ResponseContent)
{
	// Set URL.
	WinHttpClient client(util::AnsiToUnicode(url.c_str()));

	// Send http request, a GET request by default.
	client.SendHttpRequest();

	// The response header.
	wstring httpResponseHeader = client.GetResponseHeader();
	ResponseHeader = util::UnicodeToAnsi(httpResponseHeader.c_str());
	// The response content.
	wstring httpResponseContent = client.GetResponseContent();
	ResponseContent = util::UnicodeToAnsi(httpResponseContent.c_str());
	return 0;
}

int HttpClient::clinetPost(IN std::string url,IN std::string contentData,OUT std::string &ResponseHeader,OUT std::string &ResponseContent)
{
	WinHttpClient client(util::AnsiToUnicode(url.c_str()));

	// Set post data.
	string data = contentData;
	client.SetAdditionalDataToSend((BYTE *)data.c_str(), data.size());

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

	ResponseHeader = util::UnicodeToAnsi(httpResponseHeader.c_str());
	ResponseContent = util::UnicodeToAnsi(httpResponseContent.c_str());
	return 0;
}
