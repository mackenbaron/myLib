#pragma once

#include <QObject>
#include "webthread.h"
class testWeb : public QObject
{
	Q_OBJECT

public:
	testWeb(QObject *parent =0);
	~testWeb();
private:
	webthread * wthread;
};
