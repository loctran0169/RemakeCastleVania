#pragma once
#include "dsound.h"
#include "windows.h"
#include <map>
#include <string>
#include <iostream>
#include <mmsystem.h>
#include "define.h"
#include"Utils.h"
#include "Game.h"
#include <fstream>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

class CSound
{
public:
	struct WaveHeaderStruct
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
	float volume;
	void setVolume(float percentage, int type = -1);
	void loadSound(char* fileName, int type);
	void play(int type, bool infiniteLoop, int times);
	void stop(int type = -1);
	float getVolume();
	CSound(HWND hWnd);
	~CSound();
	static CSound* GetInstance();
	void mute();
	void unMute();
	void cleanUp();
	void readSoundTxt(LPCWSTR filePath = NULL);
private:
	
	static CSound * __instance;
	IDirectSound8* pDevice;
	IDirectSoundBuffer* primaryBuffer;
	std::map<int, IDirectSoundBuffer8*> soundBufferMap;
	bool isMute;

};