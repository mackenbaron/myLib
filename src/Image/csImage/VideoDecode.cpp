#include "stdafx.h"
#include "VideoDecode.h"

namespace cs
{
	VideoDecode::VideoDecode(void)
		:mCapture(NULL)
		,frame_count(0)
		,mw(0)
		,mh(0)
		,md(0)
		,mc(0)
	{
	}
	VideoDecode::~VideoDecode(void)
	{
		ReleaseOperCV();
	}

	int VideoDecode::initVideoOpenCVOperate()
	{
		mVideoInfo.height = 0;
		mVideoInfo.width = 0;
		mVideoInfo.VIDuration = 0;
		frame_count = 0;
		mw=0,mh=0,md =0,mc=0;
		if(mCapture)
			cvReleaseCapture(&mCapture);
		return 0;
	}

	int VideoDecode::openVideoOpenCVFile(char* paht)
	{
		frame_count = 0;
		mCapture = cvCreateFileCapture(paht);  //读取视频
		if(mCapture==NULL) 
		{
			return -1;
		}   

		double frames=cvGetCaptureProperty(mCapture,CV_CAP_PROP_FRAME_COUNT);//读取视频中有多少帧
		IplImage * frame;
		frame = cvQueryFrame(mCapture);//抓取帧
		FillVideoInfo(frames,frame->width,frame->height,frame->nChannels,frame->depth);
		mw = frame->width;
		mh = frame->height;
		md = frame->depth;
		mc = frame->nChannels;
		return 0;
	}

	IplImage* VideoDecode::getVideoOpenCVFrame(int conut)
	{
		cvSetCaptureProperty(mCapture, CV_CAP_PROP_POS_FRAMES, conut);//设置视频帧的读取位置
		IplImage * frame1;
		frame1 = cvQueryFrame(mCapture);//抓取帧
		if(frame1 == NULL)
			return NULL;
		else
			return frame1;	
	}

	void VideoDecode::ReleaseOperCV()
	{
		if(mCapture!=NULL)
			cvReleaseCapture(&mCapture);
	}

	double VideoDecode::getVideoFrameTime()
	{
		double _tepFrameTime =0.0;
		if(mCapture)
			_tepFrameTime =cvGetCaptureProperty(mCapture, CV_CAP_PROP_POS_MSEC );   //读取视频的帧率
		return _tepFrameTime;
	}

	double VideoDecode::getVideoFrameCount()
	{
		double _tempFrameCout=0.0;
		if(mCapture)
			_tempFrameCout = cvGetCaptureProperty(mCapture,CV_CAP_PROP_FRAME_COUNT);//读取视频中有多少帧
		return _tempFrameCout;
	}

	bool VideoDecode::FillVideoInfo(double duration,int width, int height,int Channels,int d)
	{
		mVideoInfo.width = width;
		mVideoInfo.height = height;
		mVideoInfo.VIDuration = duration;
		mVideoInfo.Channels = Channels;
		mVideoInfo.depthi = d;
		double _fps=cvGetCaptureProperty(mCapture, CV_CAP_PROP_FPS );   //读取视频的帧率
		int _vfps = 1000 / _fps;                                        //计算每帧播放的时间
		mVideoInfo.vfps = _vfps;
		mVideoInfo.fps = _fps;
		return 0;
	}

	double VideoDecode::getVideoFrameInfo(int &w,int &h,int &d,int &c)
	{
		w = mw;
		h = mh;
		d = md;
		c = mc;
		double _fps =0.0;
		if(mCapture)
			_fps=cvGetCaptureProperty(mCapture, CV_CAP_PROP_FPS );   //读取视频的帧率
		return _fps;
	}

}

