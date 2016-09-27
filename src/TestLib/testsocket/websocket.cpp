#include "websocket.h"
#include <iostream>
websocket::websocket(ISocketHandler& h)
	:HttpBaseSocket(h)
{
}


websocket::~websocket()
{
}

void websocket::IHttpServer_OnExec(const HttpRequest& req)
{
	mreq = req;
	mres.SetHeader("Server", std::string("sdf"));
	mres.SetHeader("Access-Control-Allow-Origin", "*");
	mres.SetHttpStatusCode(200);
	mres.SetHttpStatusMsg("OK");
	mres.SetContentType("text/html;charset=UTF-8");


	char _tempoutmesg[512] = { '\0' };
	sprintf(_tempoutmesg, "Request Method:%s Request URL:%s Request IP:%s", const_cast<char*>(mreq.HttpMethod().c_str()), const_cast<char*>(mreq.Uri().c_str()), const_cast<char*>(mreq.RemoteAddr().c_str()));
	//LOG(INFO)<<_tempoutmesg;
	std::cout << _tempoutmesg << std::endl;
	std::string mBufer = "";
	mBufer = "{\"State\": 1000,\"Desc\":\"Unknown error, please contact your administrator\"}";
	if (mBufer != "")
		mres.Write(mBufer.c_str(), mBufer.size());
	IHttpServer_Respond(mres);
}

void websocket::IHttpServer_Respond(const HttpResponse& res)
{
	m_res = res;

	SetHttpVersion(m_res.HttpVersion());
	SetStatus(Utility::l2string(m_res.HttpStatusCode()));
	SetStatusText(m_res.HttpStatusMsg());

	if (!ResponseHeaderIsSet("content-length"))
	{
		AddResponseHeader("content-length", Utility::l2string(m_res.GetFile().size()));
	}
	for (Utility::ncmap<std::string>::const_iterator it = m_res.Headers().begin(); it != m_res.Headers().end(); ++it)
	{
		AddResponseHeader(it->first, it->second);
	}
	std::list<std::string> vec = m_res.CookieNames();
	for (std::list<std::string>::iterator it2 = vec.begin(); it2 != vec.end(); ++it2)
	{
		AppendResponseHeader("set-cookie", m_res.Cookie(*it2));
	}
	SendResponse();

	OnTransferLimit();
}

void websocket::IHttpServer_OnResponseComplete()
{
	mreq.Reset();
	mres.Reset();
}
