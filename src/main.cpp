#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
#include "music.h"
volatile bool g_bEndMusicThread;
bool bool_user=false, bool_admin=false;  //判断用户是否处于登录状态
users* users_head =NULL;
goods* goods_head =NULL;
orders* orders_head =NULL;
users* current_user =NULL;
string admin_account ="admin"; //初始定义了管理员账户
string admin_pwd ="123456";
int main()
{
	SendToMCI("open bgm.mp3");	//打开音乐文件
	g_bEndMusicThread=false;	//初始化子线程标志位
	HANDLE hThread = (HANDLE)_beginthreadex(NULL,0,ThreadPlayMusic,NULL,0,NULL);	//创建线程
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
			cout<<"-----无效输入！请重新输入！-----"<<endl;
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
		}
		cin.sync();
		key = getchar();

	}
	cout<<endl<<"----------您已退出此程序！----------"<<endl;
	cin.sync();
	g_bEndMusicThread=true;	//通知子线程退出
	WaitForSingleObject(hThread,INFINITE);		//线程结束之后再释放资源
	SendToMCI("close bgm.mp3");	//关闭音乐文件
	getchar(); 
	return 0;
}