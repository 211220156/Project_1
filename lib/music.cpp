#include "music.h"
extern volatile bool g_bEndMusicThread;		//���߳̽����ı�־
extern bool programEND;
//������Ϣ��MCI
bool SendToMCI(string command)
{
	if(!mciSendString(command.c_str(),NULL,0,0))
		return true;
	return false;
}
 
//��MCI��ȡ��Ϣ
string GetFromMCI(std::string command)
{
	char message[20];
	mciSendString(command.c_str(),message,20,0);
	string str(message);
	return str;
}
 
//�����̵߳ķ���
unsigned __stdcall ThreadPlayMusic(LPVOID lpParameter)
{
	string Status="status bgm.mp3 mode";
	string Play="PLAY bgm.mp3";
	while(true)
	{
		Sleep(1);
		if(g_bEndMusicThread==true)		//�������̷߳��͵��˳��ź�
			break;
		string result=GetFromMCI(Status);	//��ȡ����״̬
		if(result=="stopped")
			SendToMCI(Play);	//�������ֹͣ�����²���
	}
	return 0;
}