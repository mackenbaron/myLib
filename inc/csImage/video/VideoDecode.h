#pragma once
namespace cs
{
	class VideoDecode
	{
	public:
		VideoDecode(void);
		~VideoDecode(void);
	public:
		int initVideoOpenCVOperate();
		int openVideoOpenCVFile(char* paht);
		VideoAndPictrueInfo_t	  getVideoInfo(){return mVideoInfo;}
		IplImage* getVideoOpenCVFrame(int conut);
		void ReleaseOperCV();
		double getVideoFrameTime();
		double getVideoFrameCount();
		double  getVideoFrameInfo(int &w,int &h,int &d,int &c);
	private:
		bool FillVideoInfo(double duration,int width, int height,int Channels,int d);
	private:
		VideoAndPictrueInfo_t mVideoInfo;
		CvCapture* mCapture;
		int frame_count;
		int mw,mh,md,mc;
	};
}


