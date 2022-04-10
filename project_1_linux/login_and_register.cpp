#include "trading_platform.h"
#include "calculator.h"
#include "admin.h"
#include "buyer.h"
#include "seller.h"
extern bool bool_user, bool_admin;  //判断用户是否处于登录状态
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //初始定义了管理员账户
extern string admin_pwd ;
void login(int identity)  //登录
{
	cout << endl << endl << "请输入账户：";
	if (identity == 1)//管理员登录
	{
		string name;
		getline(cin,name);
		cout << "请输入密码：";
		string pwd;
		getline(cin,pwd);
		if (name == admin_account && pwd == admin_pwd)
		{
			cout << endl << "******登录成功！按任意键进入管理员界面。******" << endl;
			getchar();
			bool_admin = true;
		}
		else
		{
			cout << endl << "******登录失败！账号或密码错误！******" << endl;
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
		}
		if (bool_admin)
			admin_menu();
	}
	else //用户登录
	{
		string name;
		getline(cin,name);
		cout << "请输入密码：";
		string pwd;
		getline(cin,pwd);
		users* h = users_head;
		bool judge = false;
		while (h != NULL)
		{
			if (name == h->name)
			{
				if (pwd == h->pwd)
				{
					if (h->status==true)
					{
						cout << endl<<"******登录成功！******" << endl;
						bool_user = true;
						judge = true;
						current_user = h;
						break;
					}
					else
					{
						cout<<endl<<"*****登录失败！账户已被封禁！*****"<<endl;
						judge=true;
						cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
					}
				}
				else
				{
					cout << endl<<"******登录失败！账户或密码错误！******" << endl;
					cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
					judge = true;
					break;
				}
			}
			h = h->next;
		}
		if (judge==false)
			cout <<endl<< "******登录失败！账户或密码错误！******" << endl<<"请输入操作(第一个字符有效，多余视为无效输入)：";
		if (bool_user)
		{
			cout << endl << "-----按任意键进入个人菜单...-----" << endl;
			getchar();
			personal_menu();
		}
	}
}

bool users_register()  //用户注册
{
	cout << endl << "**************************************************" << endl;
	cout << "请输入你要注册的用户名：";
	string name;
	getline(cin,name);
	users* h = users_head;
	bool judge_repeat = false;
	while (h != NULL)
	{
		if (h->name == name)
		{
			judge_repeat = true;
			break;
		}
		h = h->next;
	}
	if (judge_repeat)
	{
		cout << endl << endl << "-----对不起！你输入的用户名已存在！注册失败！-----"<<endl<<"按任意键返回主界面。"<<endl;
		getchar();
		return false;
	}
	else
	{
		cout << endl << "请输入你的密码：";
		string pwd1,pwd2;
		getline(cin,pwd1);
		cout << endl << "请再次确认你的密码：";
		getline(cin,pwd2);
		if (pwd1 == pwd2)
		{
			users* newone = new users;
			newone->name = name;
			newone->pwd = pwd1;
			newone->id = "U000";    //获取用户id
			if (users_head != NULL)
				newone->number = users_head->number + 1;
			else
				newone->number = 1;
			int num = newone->number;
			while (num > 0)
			{
				num /= 10;
				newone->id.pop_back();
			}
			newone->id.append(to_string(newone->number));
			cout << endl << "请输入你的联系方式：";
			getline(cin,newone->contact);
			cout << endl << "请输入你的地址：";
			getline(cin,newone->address);
			cout << endl << endl << "**************************************************" << endl;
			cout << "注册成功！当前账户id为："<<newone->id<<endl<<"余额初始为0元。" << endl;
			getchar();
			newone->next = users_head;
			users_head = newone;
			current_user = users_head;
			bool_user = true;
			modify_file(1);
			return true;
		}
		else
		{
			cout << endl << "两次密码不一致！注册失败！按任意键返回主界面。"<<endl;
			getchar();
			return false;
		}
	}
}