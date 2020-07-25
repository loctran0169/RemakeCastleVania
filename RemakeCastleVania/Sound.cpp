#include "Sound.h"


CSound* CSound::__instance = NULL;

CSound* CSound::GetInstance()
{
	if (__instance == NULL) __instance = new CSound();
	return __instance;
}

CSound::CSound()
{
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
		LPCWSTR path = ToLPCWSTR(tokens[1]);
		sounds[type] = path;
		DebugOut(L"[Sound] %d: Added \n",type);
	}
	f.close();
}

void CSound::playFromBegin(gameType type)
{
	PlaySound(sounds[type], GetModuleHandle(NULL), 1);
}

void CSound::playMulti(gameType type)
{
	PlaySound(sounds[type], GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}


CSound::~CSound()
{
}
