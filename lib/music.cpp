#include "music.h"
extern volatile bool g_bEndMusicThread;		//让线程结束的标志
extern bool programEND;
//发送信息给MCI
bool SendToMCI(string command)
{
	if(!mciSendString(command.c_str(),NULL,0,0))
		return true;
	return false;
}
 
//从MCI获取信息
string GetFromMCI(std::string command)
{
	char message[20];
	mciSendString(command.c_str(),message,20,0);
	string str(message);
	return str;
}
 
//音乐线程的方法
unsigned __stdcall ThreadPlayMusic(LPVOID lpParameter)
{
	string Status="status bgm.mp3 mode";
	string Play="PLAY bgm.mp3";
	while(true)
	{
		Sleep(1);
		if(g_bEndMusicThread==true)		//接收主线程发送的退出信号
			break;
		string result=GetFromMCI(Status);	//获取音乐状态
		if(result=="stopped")
			SendToMCI(Play);	//如果音乐停止，重新播放
	}
	return 0;
}