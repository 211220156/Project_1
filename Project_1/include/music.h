#pragma once
#include <iostream>
#include<windows.h>
#include <process.h>
using namespace std;
#pragma comment(lib,"Winmm.lib")
extern volatile bool g_bEndMusicThread;	
bool SendToMCI(string command);
string GetFromMCI(std::string command);
unsigned __stdcall ThreadPlayMusic(LPVOID lpParameter);