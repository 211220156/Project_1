#include "trading_platform.h"
#include "calculator.h"
#include "admin.h"
#include "buyer.h"
#include "seller.h"
extern bool bool_user, bool_admin;  //�ж��û��Ƿ��ڵ�¼״̬
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //��ʼ�����˹���Ա�˻�
extern string admin_pwd ;
void login(int identity)  //��¼
{
	cout << endl << endl << "�������˻���";
	if (identity == 1)//����Ա��¼
	{
		string name;
		cin.sync();
		getline(cin,name);
		cout << "���������룺";
		string pwd;
		cin.sync();
		char c=getch();
		while (c!=13)
		{
			pwd.push_back(c);
			cout<<"*";
			c=getch();
		}
		if (name == admin_account && pwd == admin_pwd)
		{
			cout << endl << "******��¼�ɹ�����������������Ա���档******" << endl;
			cin.sync();
			getchar();
			bool_admin = true;
		}
		else
		{
			cout << endl << "******��¼ʧ�ܣ��˺Ż��������******" << endl;
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
		}
		if (bool_admin)
			admin_menu();
	}
	else //�û���¼
	{
		string name;
		cin.sync();
		getline(cin,name);
		cout << "���������룺";
		string pwd;
		cin.sync();
		char c=getch();
		while (c!=13)
		{
			pwd.push_back(c);
			cout<<"*";
			c=getch();
		}
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
						cout << endl<<"******��¼�ɹ���******" << endl;
						bool_user = true;
						judge = true;
						current_user = h;
						break;
					}
					else
					{
						cout<<endl<<"*****��¼ʧ�ܣ��˻��ѱ������*****"<<endl;
						judge=true;
						cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
					}
				}
				else
				{
					cout << endl<<"******��¼ʧ�ܣ��˻����������******" << endl;
					cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
					judge = true;
					break;
				}
			}
			h = h->next;
		}
		if (judge==false)
			cout <<endl<< "******��¼ʧ�ܣ��˻����������******" << endl<<"���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
		if (bool_user)
		{
			cout << endl << "-----�������������˲˵�...-----" << endl;
			cin.sync();
			getchar();
			personal_menu();
		}
	}
}

bool users_register()  //�û�ע��
{
	cout << endl << "**************************************************" << endl;
	cout << "��������Ҫע����û�����";
	string name;
	cin.sync();
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
		cout << endl << endl << "-----�Բ�����������û����Ѵ��ڣ�ע��ʧ�ܣ�-----"<<endl<<"����������������档"<<endl;
		cin.sync();
		getchar();
		return false;
	}
	else
	{
		cout << endl << "������������룺";
		string pwd1,pwd2;
		cin.sync();
		getline(cin,pwd1);
		cout << endl << "���ٴ�ȷ��������룺";
		cin.sync();
		getline(cin,pwd2);
		if (pwd1 == pwd2)
		{
			users* newone = new users;
			newone->name = name;
			newone->pwd = pwd1;
			newone->id = "U000";    //��ȡ�û�id
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
			cout << endl << "�����������ϵ��ʽ��";
			cin.sync();
			getline(cin,newone->contact);
			cout << endl << "��������ĵ�ַ��";
			cin.sync();
			getline(cin,newone->address);
			cout << endl << endl << "**************************************************" << endl;
			cout << "ע��ɹ�����ǰ�˻�idΪ��"<<newone->id<<endl<<"����ʼΪ0Ԫ��" << endl;
			cin.sync();
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
			cout << endl << "�������벻һ�£�ע��ʧ�ܣ�����������������档"<<endl;
			cin.sync();
			getchar();
			return false;
		}
	}
}