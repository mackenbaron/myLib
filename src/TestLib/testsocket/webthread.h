#pragma once

#include <QThread>

class webthread : public QThread
{
	Q_OBJECT

public:
	webthread(QObject *parent);
	~webthread();
protected:
	void run();
};
