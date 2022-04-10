#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <algorithm>
using namespace std;

struct goods {
	string id;
	string name;
	double price = 0;
	int num=0;//商品个数
	string description;
	string seller_id;
	string on_shelf_time;
	int number = 0;//无实际意义，方便生成id
	int status = 1;//1表示销售中，0表示已下架
	goods* next;
};
struct users {
	string id;
	string name;
	string pwd;
	string contact;
	string address;
	int number = 0;//无实际意义，方便生成id
	double money = 0;
	bool status=true;
	string money_exp="0";
	string message="";
	users* next;
};
struct orders {
	string id;
	string g_id;
	double amount = 0;//单价
	int num=0;//数量
	string time;
	string seller_id;
	string buyer_id;
	int number=0;//用于获取订单号
	orders* next;
};
extern bool bool_user, bool_admin;  //判断用户是否处于登录状态
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //初始定义了管理员账户
extern string admin_pwd ; //初始定义了管理员密码
string get_time();//用于获取交易的时间
string get_accurate_time();

void reverse(int kind); //按原先顺序输出，要反转一次 1表示反转用户，0商品，-1订单
int search(const char str1[],const char str2[]);
void modify_file(int kind);
void Init_file(users* &users_head,goods* &goods_head,orders* &orders_head);
void Init_View();
void personal_info();//个人信息界面
void personal_menu();//用户个人菜单
void modify_chat_history(string content);

bool judge_price(string price);//helper函数，判断输入的是否是合法价格
bool judge_num(string num);//helper函数，判断输入的是否为合法数量
void login(int identity);//用户登录
bool users_register();//用户注册
void init();//初始化界面

void modify_sql(string ans);
