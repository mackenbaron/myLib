#pragma once

typedef struct VideoAndPictrueInfo
{
	std::string inputVideoPicturePath;
	int width;
	int height;
	double VIDuration;
	int Channels;
	int depthi;
	int vfps;
	int fps;
	VideoAndPictrueInfo()
		:width(0)
		,height(0)
		,VIDuration(0)
		,Channels(-1)
		,depthi(-1)
		,inputVideoPicturePath("")
		,vfps(0)
		,fps(0)
	{

	}
	void cleanData()
	{
		inputVideoPicturePath = "";
		width = -1;
		height = -1;
		VIDuration = -1;
		Channels = -1;
		depthi = -1;
		vfps = 0;
		fps = 0;
	}
}VideoAndPictrueInfo_t;