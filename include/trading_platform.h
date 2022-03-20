#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <fstream>
using namespace std;

struct goods {
	string id;
	string name;
	double price = 0;
	int num=0;//��Ʒ����
	string description;
	string seller_id;
	string on_shelf_time;
	int number = 0;//��ʵ�����壬��������id
	int status = 1;//1��ʾ�����У�0��ʾ���¼�
	goods* next;
};
struct users {
	string id;
	string name;
	string pwd;
	string contact;
	string address;
	int number = 0;//��ʵ�����壬��������id
	double money = 0;
	bool status=true;
	string money_exp="0";
	users* next;
};
struct orders {
	string id;
	string g_id;
	double amount = 0;//����
	int num=0;//����
	string time;
	string seller_id;
	string buyer_id;
	int number=0;//���ڻ�ȡ������
	orders* next;
};
extern bool bool_user, bool_admin;  //�ж��û��Ƿ��ڵ�¼״̬
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //��ʼ�����˹���Ա�˻�
extern string admin_pwd ; //��ʼ�����˹���Ա����
string get_time();//���ڻ�ȡ���׵�ʱ��
void reverse(int kind); //��ԭ��˳�������Ҫ��תһ�� 1��ʾ��ת�û���0��Ʒ��-1����
int search(const char str1[],const char str2[]);
void modify_file(int kind);
void Init_file(users* &users_head,goods* &goods_head,orders* &orders_head);
void Init_View();
void personal_info();//������Ϣ����
void personal_menu();//�û����˲˵�

/*void admin_menu();//����Ա�˵�
void admin_all_goods();
void admin_search_good(string name);
void admin_all_orders();
void admin_all_users();
void admin_remove_good(string id);
void admin_ban_user(string id);


void buyer();//��ҽ���
void buyer_all_goods();
void buyer_search_good(string name);
void buyer_all_orders();
void buyer_good_details(string id);
void buyer_purchase_good(string content);
void buyer_remove_good(string id);

void seller();//���ҽ���
void seller_all_goods();
void seller_all_orders();
void seller_remove_good(string id);
void seller_modify_good(int kind,string content,string id);
void seller_publish_good(string content);*/

bool judge_price(string price);//helper�������ж�������Ƿ��ǺϷ��۸�
bool judge_num(string num);//helper�������ж�������Ƿ�Ϊ�Ϸ�����
void login(int identity);//�û���¼
bool users_register();//�û�ע��
void init();//��ʼ������

void modify_sql(string ans);
