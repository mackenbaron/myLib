#include "webthread.h"
#include "websocket.h"
#include <iostream>
webthread::webthread(QObject *parent)
	: QThread(parent)
{
}

webthread::~webthread()
{
}

void webthread::run()
{
	StdoutLog log;
	SocketHandler h(&log);
	ListenSocket<websocket> l(h);
	h.SetNumberOfThreads(10);
	if (l.Bind(8080, 10))
	{
		//LOG(ERROR)<<"Bind to Port"<<mport<<"Failed";
		return;
	}
	h.Add(&l);
	//LOG(INFO)<<"Listening on Port"<<mport;
#ifdef WIN32
	char _tempsrc[512] = { '\0' };
	sprintf(_tempsrc, "ZNBYServer_%s (Listening Port %d)", "12", 8080);
	/*SetConsoleTitle(AnsiToUnicode(_tempsrc));*/
#endif
	while (true)
	{
		h.Select(1, 0);
	}
	std::cout << "Exiting..." << std::endl;
}
