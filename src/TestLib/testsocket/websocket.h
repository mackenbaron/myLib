#pragma once

#include <Sockets/HttpBaseSocket.h>
#include <Sockets/StdoutLog.h>
#include <Sockets/ListenSocket.h>
#include <Sockets/SocketHandlerEp.h>
#include <Sockets/TcpSocket.h>
#include <Sockets/HttpDebugSocket.h>
#include <Sockets/Json.h>
#include <Sockets/HttpdSocket.h>
#include <Sockets/SocketHandler.h>
#include <Sockets/HttpPostSocket.h>
#include <Sockets/HttpPutSocket.h>
#include <Sockets/HttpdForm.h>

class websocket :public HttpBaseSocket
{
public:
	websocket(ISocketHandler& h);
	virtual ~websocket();
public:
	void IHttpServer_OnExec(const HttpRequest& req);
	void IHttpServer_Respond(const HttpResponse& res);
	void IHttpServer_OnResponseComplete();
private:
	HttpRequest mreq;
	HttpResponse mres;
};

