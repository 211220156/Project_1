#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
#include "music.h"
volatile bool g_bEndMusicThread;
bool bool_user=false, bool_admin=false;  //�ж��û��Ƿ��ڵ�¼״̬
users* users_head =NULL;
goods* goods_head =NULL;
orders* orders_head =NULL;
users* current_user =NULL;
string admin_account ="admin"; //��ʼ�����˹���Ա�˻�
string admin_pwd ="123456";
int main()
{
	SendToMCI("open bgm.mp3");	//�������ļ�
	g_bEndMusicThread=false;	//��ʼ�����̱߳�־λ
	HANDLE hThread = (HANDLE)_beginthreadex(NULL,0,ThreadPlayMusic,NULL,0,NULL);	//�����߳�
	Init_file(users_head,goods_head,orders_head);
	Init_View();
	cin.sync();
	int key=getchar();
	while (key!=52)
	{
		switch (key)
		{
		case 49:
		{
			login(0);
			break;
		}
		case 50:
		{
			if (users_register())
				personal_menu();
			else
				Init_View();
			break;
		}
		case 51:
		{
			login(1);
			break;
		}
		default:
			cout<<"-----��Ч���룡���������룡-----"<<endl;
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
		}
		cin.sync();
		key = getchar();

	}
	cout<<endl<<"----------�����˳��˳���----------"<<endl;
	cin.sync();
	g_bEndMusicThread=true;	//֪ͨ���߳��˳�
	WaitForSingleObject(hThread,INFINITE);		//�߳̽���֮�����ͷ���Դ
	SendToMCI("close bgm.mp3");	//�ر������ļ�
	getchar(); 
	return 0;
}