#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
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
	Init_file(users_head,goods_head,orders_head);
	Init_View();
	string key;
	getline(cin,key);
	while (key[0]!=52)
	{
		switch (key[0])
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
		getline(cin,key);

	}
	cout<<endl<<"----------您已退出此程序！----------"<<endl;
	getchar(); 
	return 0;
}