#include "testWeb.h"

testWeb::testWeb(QObject *parent)
	: QObject(parent)
{
	wthread = new webthread(this);
	wthread->start();
}

testWeb::~testWeb()
{
}
