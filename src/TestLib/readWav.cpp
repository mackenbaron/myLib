// readWav.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#if 0
#include "stdlib.h"
#include "stdio.h"


int main()
{
	int i;   //用作循环计数
	unsigned char ch[100];  //用来存储wav文件的头信息
	FILE *fp;

	if((fp=fopen("1.wav","rb"))==NULL) //若打开文件失败，退出
	{
		printf("can't open this file\n");
		exit(0);
	}

	/**********输出wav文件的所有信息**********/
	printf("该wav文件的所有信息:");
	for(i=0;i<58;i++)
	{
		ch[i]=fgetc(fp); //每次读取一个字符，存在数组ch中
		if(i%16==0)      //每行输出16个字符对应的十六进制数
			printf("\n");
		if(ch[i]<16)     //对小于16的数，在前面加0，使其用8bit显示出来
			printf("0%x ",ch[i]);   
		else
			printf("%x ",ch[i]);
	}

	/*********RIFF WAVE Chunk的输出*********/
	printf("\n\nRIFF WAVE Chunk信息:");
	//输出RIFF标志
	printf("\nRIFF标志:");
	for(i=0;i<4;i++)
	{
		printf("%x ",ch[i]);
	}

	//输出size大小
	printf("\nsize:ox");
	for(i=7;i>=4;i--) //低字节表示数值低位，高字节表示数值高位
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	//输出WAVE标志
	printf("\nWAVE标志:");
	for(i=8;i<12;i++)
	{
		if(ch[i]<16)
			printf("0%x ",ch[i]);
		else
			printf("%x ",ch[i]);
	}

	/*******Format Chunk的输出*******/
	printf("\n\nFormat Chunk信息:");
	//输出fmt 标志
	printf("\nfmt 标志:");
	for(i=12;i<16;i++)
	{
		if(ch[i]<16)
			printf("0%x ",ch[i]);
		else
			printf("%x ",ch[i]);
	}

	//输出size段 
	printf("\nsize:ox");
	for(i=19;i>15;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	//输出编码方式
	printf("\n编码方式:ox");
	for(i=21;i>19;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	//输出声道数目
	printf("\n声道数目:ox");
	for(i=23;i>21;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	if(ch[i+1]==1)   //1表示单声道，2表示双声道
		printf(" 单声道");
	else
		printf(" 双声道");

	//输出采样频率 
	printf("\n采样频率:ox");
	for(i=27;i>23;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	//输出每秒所需字节数 
	printf("\n每秒所需字节数:ox");
	for(i=31;i>27;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	//输出数据块对齐单位 
	printf("\n数据块对齐单位:ox");
	for(i=33;i>31;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	//输出每个采样所需bit数 
	printf("\n每个采样所需bit数:ox");
	for(i=35;i>33;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	//输出附加信息
	if(ch[16]==18)  //若Format Chunk的size大小为18，则该模块的最后两个字节为附加信息
	{               //若为16，则无附加信息
		printf("\n附加信息:ox");
		for(i=37;i>35;i--)
		{
			if(ch[i]<16)
				printf("0%x",ch[i]);
			else
				printf("%x",ch[i]);
		}
	}

	/*******Fact Chunk的输出*******/
	printf("\n\nFact Chunk信息:");
	//输出fact标志 
	printf("\nfact标志:");
	for(i=38;i<42;i++)
	{
		if(ch[i]<16)
			printf("0%x ",ch[i]);
		else
			printf("%x ",ch[i]);
	}

	//输出size 
	printf("\nsize:ox");
	for(i=45;i>41;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	//输出data段数据
	printf("\ndata段数据:");
	for(i=46;i<50;i++)
	{
		if(ch[i]<16)
			printf("0%x ",ch[i]);
		else
			printf("%x ",ch[i]);
	}

	/*******Data Chunk的输出*******/
	printf("\n\nData Chunk信息:");
	//输出data标志
	printf("\ndata标志:");
	for(i=50;i<54;i++)
	{
		if(ch[i]<16)
			printf("0%x ",ch[i]);
		else
			printf("%x ",ch[i]);
	}

	//输出数据大小
	printf("\n数据大小:ox");
	for(i=57;i>53;i--)
	{
		if(ch[i]<16)
			printf("0%x",ch[i]);
		else
			printf("%x",ch[i]);
	}

	printf("\n");

	fclose(fp);
}

#else 

#include <STDIO.H>
#include <STDLIB.H>
#include <WINDOWS.H>
#include <TIME.H>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

typedef UCHAR Uint8;
typedef UCHAR uint8_t;
typedef USHORT Uint16;
typedef USHORT uint16_t;
typedef UINT32 Uint32;
typedef UINT32 uint32_t;

typedef struct _WavBuffer{
	Uint8* wav_buffer;//数据缓存
	Uint32 wav_length;//数据缓存大小
	Uint8* wav_pos;//播放位置
	Uint32 wav_lastlength;//剩余数据大小
}WavBuffer;
typedef struct _WAVE_FORMAT{
	uint16_t	wFormatTag;//格式一般PCM,1
	uint16_t	nChannels;//声道数mono 1 单声道 stereo 2 双声道
	uint32_t	nSamplesPerSec;//采样率(每秒采样数) 常见 11.025 kHz,22.05  kHz,44.1   kHz,48     kHz,96     kHz
	uint32_t   nAvgBytesPerSec;//平均每秒字节数 声道数*采样率*采样位数/8
	uint16_t    nBlockAlign;//对齐字节 声道数*采样位数/8 (单声道8bit 1Byte 双声道16bit 4Byte)
	uint16_t    wBitsPerSample;//采样位数8bit 16bit
}WAVE_FORMAT;
//从Wav文件读取数据返回音频格式，数据，数据长度,0正常，-1错误
int ReadWavFromFile(const char*filename,WAVE_FORMAT*format,uint8_t**buffer,uint32_t*length);

DWORD CALLBACK waveOutProc(HWAVEOUT hwo,UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2);
//每次播放缓存大小
#define PLAYBUFFERLENGTH 16384

//使用sndPlaySound函数从文件播放
#define USE_PLAYSOUND_FROM_FILE 0

#define WAVEHDR_NUM 2

int main(int args,char**argv){
	WavBuffer wavbuff={0};
	WAVE_FORMAT waveFormat={0};
	WAVEFORMATEX waveFormatEx={0};
	HWAVEOUT    hWaveOut=NULL;
	WAVEHDR hdr[WAVEHDR_NUM]={0};
	const char *filename="1.wav";
	int i=0;
	//sndPlaySound播放文件,其它参考PlaySound
	//SND_SYNC同步播放，SND_ASYNC异步播放
#if USE_PLAYSOUND_FROM_FILE
	printf("从文件播放声音!\n");
	sndPlaySound(filename,SND_SYNC);
#else

	if(ReadWavFromFile(filename,&waveFormat,&wavbuff.wav_buffer,&wavbuff.wav_length)==0){
		printf("读取成功!\n");
		printf("音频编码:%s(%hu)\n",waveFormat.wFormatTag==1?"PCM":"??",waveFormat.wFormatTag);
		printf("声道数:%hu \n",waveFormat.nChannels);
		printf("采样率:%u Hz\n",waveFormat.nSamplesPerSec);
		printf("位率:%u bps\n",waveFormat.nAvgBytesPerSec*8);
		printf("对齐字节:%hu byte\n",waveFormat.nBlockAlign);
		printf("采样位数:%u bit\n",waveFormat.wBitsPerSample);
		printf("数据大小:%u\n",wavbuff.wav_length);
		printf("预测时长:%u s\n",wavbuff.wav_length/(waveFormat.nSamplesPerSec*waveFormat.nChannels*waveFormat.wBitsPerSample/8));
	}else{
		printf("读取失败!\n");
		return -1;
	}
	printf("默认方法播放声音!\n");
	memcpy(&waveFormatEx,&waveFormat,sizeof(WAVE_FORMAT));
	printf("音频输出设备数量:%u\n",waveOutGetNumDevs());
	if(waveOutOpen(&hWaveOut,0,&waveFormatEx,(DWORD)(waveOutProc),0,CALLBACK_FUNCTION)!=0){
		printf("打开音频设备错误\n");
		goto exit;
	}
	wavbuff.wav_pos=wavbuff.wav_buffer;
	wavbuff.wav_lastlength=wavbuff.wav_length;
	//准备音频缓冲区
	for(i=0;i<WAVEHDR_NUM;i++){
		hdr[i].dwBufferLength=PLAYBUFFERLENGTH;
		hdr[i].lpData=(LPSTR)wavbuff.wav_pos;
		hdr[i].dwUser=(DWORD_PTR)&wavbuff;
		wavbuff.wav_pos+=PLAYBUFFERLENGTH;
		wavbuff.wav_lastlength-=PLAYBUFFERLENGTH;
		waveOutPrepareHeader(hWaveOut,&hdr[i],sizeof(WAVEHDR));
	}
	//写数据
	for(i=0;i<WAVEHDR_NUM;i++){
		waveOutWrite(hWaveOut,&hdr[i],sizeof(WAVEHDR));
	}

	while(wavbuff.wav_lastlength>0){
		Sleep(100);
	}
	waveOutPause(hWaveOut);
	//释放区间
	for(i=0;i<WAVEHDR_NUM;i++){
		waveOutUnprepareHeader(hWaveOut,&hdr[i],sizeof(WAVEHDR));
	}

	waveOutClose(hWaveOut);
exit:
	free(wavbuff.wav_buffer);
#endif
	return 0;
}

DWORD CALLBACK waveOutProc(HWAVEOUT hwo,UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2){
	WAVEHDR*pHDR=(WAVEHDR*)dwParam1;
	switch (uMsg){
	case WOM_OPEN:
		printf("WOM_OPEN\n");
		break;
	case WOM_CLOSE:
		printf("WOM_CLOSE\n");
		break;
	case WOM_DONE:{
		WavBuffer*pwavbuff=NULL;
		int templength=0;			
		pwavbuff=(WavBuffer*)pHDR->dwUser;
		templength=pwavbuff->wav_lastlength<PLAYBUFFERLENGTH?pwavbuff->wav_lastlength:PLAYBUFFERLENGTH;
		pHDR->lpData=(LPSTR)pwavbuff->wav_pos;
		pHDR->dwBufferLength=templength;
		pwavbuff->wav_pos+=templength;
		pwavbuff->wav_lastlength-=templength;
		waveOutWrite(hwo,pHDR,sizeof(WAVEHDR));
				  }
				  break;
	default:
		printf("%x\n",uMsg);
	}
	return 0;
}

typedef struct _RIFF_HEADER{
	uint32_t RiffID;//'RIFF'
	uint32_t RiffSize;//文件总长度-8
	uint32_t RiffFormat;//类型'WAVE'
}RIFF_HEADER;
typedef struct _BLOCK_HEADER{
	uint32_t BlockID;//'fmt ' 'fact' 'Data'
	uint32_t BlockSize;//
}BLOCK_HEADER;
#define MAKETAG(a,b,c,d)   ((a&0xff)|((b<<8)&(0xff00))|((c<<16)&(0xff0000))|((d<<24)&(0xff000000)))

int ReadWavFromFile(const char*filename,WAVE_FORMAT*format,uint8_t**buffer,uint32_t*length){
	RIFF_HEADER Riff_Header={0};
	BLOCK_HEADER BlockHeader={0};
	uint32_t dataPos=0;
	uint32_t dataSize=0;
	FILE*fp=fopen(filename,"rb");
	if(fp==NULL)
		return -1;
	fread(&Riff_Header,1,sizeof(Riff_Header),fp);
	//检查WAVE标签
	if((Riff_Header.RiffID==MAKETAG('R','I','F','F'))&&(Riff_Header.RiffFormat==MAKETAG('W','A','V','E'))){
		printf("这是WAV文件\n");
	}else{
		printf("这不是WAV文件\n");
		fclose(fp);
		return -1;
	}
	while(fread(&BlockHeader,1,sizeof(BlockHeader),fp)==sizeof(BlockHeader)){
		//		printf("BlockID:%0.4s BlockSize:%u\n",(char*)&(BlockHeader.BlockID),BlockHeader.BlockSize);
		//读取格式信息
		if(BlockHeader.BlockID==MAKETAG('f','m','t',' ')){
			uint32_t Pos=ftell(fp);
			fread(format,1,sizeof(WAVE_FORMAT),fp);
			fseek(fp,Pos,SEEK_SET);
		}
		//读取数据信息
		if(BlockHeader.BlockID==MAKETAG('d','a','t','a')){
			dataPos=ftell(fp);
			dataSize=BlockHeader.BlockSize;
		}
		if(BlockHeader.BlockSize>0){
			fseek(fp,BlockHeader.BlockSize,SEEK_CUR);
		}else{
			break;
		}
	}
	if(dataSize>0){
		fseek(fp,dataPos,SEEK_SET);
		*buffer=(uint8_t*)malloc(dataSize*sizeof(uint8_t));
		*length=dataSize;
		fread(*buffer,1,dataSize,fp);
	}
	fclose(fp);
	return dataSize>0?0:-1;
}
#endif