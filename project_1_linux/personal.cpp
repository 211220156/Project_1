#include "trading_platform.h"
#include "calculator.h"
#include "admin.h"
#include "buyer.h"
#include "seller.h"
using namespace std;
extern bool bool_user, bool_admin;  //判断用户是否处于登录状态
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //初始定义了管理员账户
extern string admin_pwd ;
void personal_menu() //个人界面
{
	system("clear");
	cout << "================================================================================" << endl;
	cout << "1.注销登录 2.我是买家 3.我是卖家 4.个人信息管理" << endl;
	cout << "================================================================================" << endl;
	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
	string key;
	getline(cin,key);
	switch (key[0])
	{
	case 49:
	{
		cout << endl << "******注销登录成功！******"<<endl<<endl<<"-----按任意键返回主菜单-----"<<endl;
		getchar();
		bool_user = false;
		current_user = NULL;
		Init_View();
		break;
	}
	case 50:
	{
		buyer();
		break;
	}
	case 51:
	{
		seller();
		break;
	}
	case 52:
	{
		personal_info();
		break;
	}
	default:
		cout << endl << "请输入对应的操作！！" << endl;
		getchar();
		personal_menu();
		break;
	}
}

void personal_info()  //个人信息处理
{
	system("clear");
	cout << "================================================================================" << endl;
	cout << "1.返回用户主界面 2.修改信息 3.查看信息 4.充值" << endl;
	cout << "================================================================================" << endl;
	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
	string key;
	getline(cin,key);
	string amount;
	while (key[0] != 49)
	{
		switch (key[0])
		{
		case 50:
		{
			cout << endl << "请选择修改的属性（1.用户名 2.联系方式 3.地址 4.密码）：";
			string option;
			getline(cin,option);
			switch (option[0])
			{
			case 49:
			{
				cout << endl << "请输入修改后的用户名：";
				string name;
				getline(cin,name);
				users* h=users_head;
				bool judge_repeat=false;
				while (h!=NULL)
				{
					if (h->name==name)
					{
						judge_repeat=true;
						break;
					}
					h=h->next;
				}
				if (judge_repeat)
				{
					cout << endl << "****************************************" << endl << "修改失败！用户名已被使用！" << endl;
				}
				else
				{
					cout << endl << "****************************************" << endl << "修改成功！" << endl;
					current_user->name=name;
					modify_file(1);
				}
				break;
			}
			case 50:
			{
				cout << endl << "请输入修改后的联系方式：";
				string contact;
				getline(cin,contact);
				cout << endl << "****************************************" << endl << "修改成功！" << endl;
				current_user->contact = contact;
				modify_file(1);
				break;
			}
			case 51:
			{
				cout << endl << "请输入修改后的地址：";
				string address;
				getline(cin,address);
				cout << endl << "****************************************" << endl << "修改成功！" << endl;
				current_user->address = address;
				modify_file(1);
				break;
			}
			case 52:
			{
				cout << endl << "请输入修改后的密码：";
				string pwd;
				getline(cin,pwd);
				cout << endl << "****************************************" << endl << "修改成功！" << endl;
				current_user->pwd = pwd;
				modify_file(1);
				break;
			}
			default:
				cout<<endl<<"-----输入无效！请重新输入！-----"<<endl<<endl;
				break;
			}
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 51:
		{
			cout <<endl<< "********************"<<endl;
			cout << "用户名：" << current_user->name << endl;
			cout << "联系方式：" << current_user->contact << endl;
			cout << "地址：" << current_user->address << endl;
	//		cout << "余额：" << current_user->money << endl;
			cout<<"余额：";
			current_user->money=stod(calculator(current_user->money_exp));
			cout<<current_user->money<<endl;
			cout << "********************" << endl;
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 52:
		{
			cout << endl << "请输入充值金额：";
			while (1)
			{
				getline(cin,amount);
				if (amount!="")
					break;
			}
			int i=0;
			bool judge_double=false;//判断输入的是否是小数
			bool judge=true;//判断输入是否合法
			while (i<amount.size())
			{
				if (amount[i]=='.')
				{
					judge_double=true;
					if ((amount[i+1]>='0' && amount[i+1]<='9') && i+2==amount.size())
					{
						cout << endl << "****************************************" << endl << "充值成功！" << endl;
						cout << "当前余额：";
						//current_user->money += amount;
						current_user->money_exp+=("+"+amount);//生成表达式
						current_user->money=stod(calculator(current_user->money_exp));//通过表达式计算余额
						cout<<current_user->money<<endl;
						modify_file(1);
						cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
						break;
					}
					else
					{
						judge=false;
						cout << endl << "****************************************" << endl << "充值失败！" << endl;
						cout<<"您输入了错误格式的金额！"<<endl<<endl;
						cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
						break;
					}
				}
				else if (amount[i]<'0' || amount[i]>'9')
				{
					judge=false;
					cout << endl << "****************************************" << endl << "充值失败！" << endl;
					cout<<"您输入了错误格式的金额！"<<endl<<endl;
					cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
					break;
				}
				i++;
			}
			if (judge && judge_double==false)
			{
				cout << endl << "****************************************" << endl << "充值成功！" << endl;
				cout << "当前余额：";
				//current_user->money += amount;
				current_user->money_exp+=("+"+amount);//生成表达式
				current_user->money=stod(calculator(current_user->money_exp));//通过表达式计算余额
				cout<<current_user->money<<endl;
				modify_file(1);
				cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			}
			break;
		}
		default:
			cout<<endl<<"输入无效，请重新输入！"<<endl<<endl;
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		getline(cin,key);
	}
	personal_menu();
}
