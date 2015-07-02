#include "util.h"
unsigned int DataBuffer::preflen = 1048576; // 2^20

DataBuffer::DataBuffer()
	:datalen(0), data(NULL)
{
	data = new unsigned char[DataBuffer::preflen];
	memset(data, '\0', DataBuffer::preflen);
}

DataBuffer::~DataBuffer()
{
	delete[] data;
	datalen = 0;
}