#include "Sound.h"


CSound* CSound::__instance = nullptr;

CSound* CSound::GetInstance()
{
	if (__instance == NULL) __instance = new CSound(CGame::GetInstance()->getHwnd());
	return __instance;
}

CSound::CSound(HWND hWnd)
{
	primaryBuffer = 0;
	HRESULT result;

	DSBUFFERDESC bufferDesc; //describe the buffer

	result = DirectSoundCreate8(NULL, &pDevice, NULL);

	if (FAILED(result))
	{
		DebugOut(L"Can not create device \n");
		return;
	}
	
	if (FAILED(result = pDevice->SetCooperativeLevel(hWnd, DSSCL_PRIORITY))) // set the cooperative level.
	{
		DebugOut(L"thất bại sound device \n", GetTickCount());
		return;
	}

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = pDevice->CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);

	if (FAILED(result))
	{
		DebugOut(L"Can not create primaryBuffer \n");
		return;
	}

	volume = 100.0f;
	isMute = false;
	readSoundTxt(L"sounds\\0soundFile.txt");
}

void CSound::readSoundTxt(LPCWSTR filePath)
{
	ifstream f;
	f.open(filePath);
	char str[1024];
	while (f.getline(str, 1024))
	{
		string line(str);
		vector<string> tokens = split(line);

		if (tokens.size() < 2) return; // skip invalid lines

		int type = atoi(tokens[0].c_str());
		char *path = new char[tokens[01].length() + 1];
		strcpy(path, tokens[1].c_str());
		loadSound(path, type);
	}
	f.close();
}

CSound::~CSound()
{
	for (auto it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
	{
		if (it->second)
		{
			it->second->Release();
			it->second = NULL;
		}

	}
	if (primaryBuffer)
		primaryBuffer->Release();
	if (pDevice)
		pDevice->Release();
	pDevice = NULL;

	primaryBuffer = NULL;


}


float CSound::getVolume()
{
	return volume;
}

void CSound::loadSound(char* fileName, int type)
{
	if (soundBufferMap.find(type) != soundBufferMap.end())
		return;
	FILE* filePtr;
	WaveHeaderStruct waveHeaderStruct;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* wavData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	int error = fopen_s(&filePtr, fileName, "rb");
	if (error != 0)
	{
		DebugOut(L" Can not load: %s", fileName);
		return;
	}

	fread(&waveHeaderStruct, sizeof(WaveHeaderStruct), 1, filePtr);
	//fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);

	if ((waveHeaderStruct.format[0] != 'W') || (waveHeaderStruct.format[1] != 'A') ||
		(waveHeaderStruct.format[2] != 'V') || (waveHeaderStruct.format[3] != 'E'))
	{
		DebugOut(L" file format does not support: %s", fileName);
	}

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeaderStruct.sampleRate;
	waveFormat.wBitsPerSample = waveHeaderStruct.bitsPerSample;
	waveFormat.nChannels = waveHeaderStruct.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeaderStruct.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = 0;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;
	//IDirectSoundBuffer8

	//long result = pDevice->CreateSoundBuffer(&bufferDesc, &secondaryBuffer, NULL);

	pDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	long result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&(*pSecondaryBuffer));

	tempBuffer->Release();
	tempBuffer = 0;

	if (FAILED(result))
	{
		DebugOut(L" Can not create secondaryBuffer ");
		return;
	}

	//fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET); // move the filePointer cursor to data section

	fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET);


	wavData = new unsigned char[waveHeaderStruct.dataSize];



	fread(wavData, waveHeaderStruct.dataSize, 1, filePtr);

	error = fclose(filePtr);
	if (error != 0)
	{
		DebugOut(L" Can not close file ");
	}

	result = (*pSecondaryBuffer)->Lock(0, waveHeaderStruct.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	if (FAILED(result))
	{
		return;
	}

	memcpy(bufferPtr, wavData, waveHeaderStruct.dataSize);

	(*pSecondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	if (wavData != NULL)
		delete wavData;
	wavData = 0;
	long tempVolume = (volume) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);
	DebugOut(L"[Sound] loaded sound type = %d\n", type);
	soundBufferMap[type] = secondaryBuffer;


}

void CSound::play(int type, bool infiniteLoop, int times)
{
	DebugOut(L"play sound type = %d \n", type);
	if (isMute)
	{
		return;
	}
	std::map< int , IDirectSoundBuffer8*> ::iterator it;
	it = soundBufferMap.find(type);
	if (it == soundBufferMap.end()) {
		return;
	}
	if (infiniteLoop)
	{
		it->second->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		it->second->Stop();
		it->second->SetCurrentPosition(0);
		it->second->Play(0, 0, times - 1);
	}

}

void CSound::stop(int type)
{
	if (type == -1)
	{
		for (std::map< int, IDirectSoundBuffer8*> ::iterator it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
	else
	{
		std::map< int, IDirectSoundBuffer8*> ::iterator it;
		it = soundBufferMap.find(type);
		if (it == soundBufferMap.end())
			return;
		else it->second->Stop();
	}
}

void CSound::mute()
{
	isMute = true;
	CSound::GetInstance()->stop();
}

void CSound::unMute()
{
	isMute = false;
}

void CSound::cleanUp()
{
	delete this;
}
