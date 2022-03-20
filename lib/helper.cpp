#include "trading_platform.h"
#include "calculator.h"
extern bool bool_user, bool_admin;  //�ж��û��Ƿ��ڵ�¼״̬
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //��ʼ�����˹���Ա�˻�
extern string admin_pwd ;
string get_time()//���ڻ�ȡ���׵�ʱ��
{
	time_t rawtime = time(0);
	struct tm localtm = *localtime(&rawtime);//ת��Ϊtm struct
	int year = localtm.tm_year + 1900;
	int month = localtm.tm_mon + 1;
	int day = localtm.tm_mday;
	string date1, date2, date3;
	date1 = to_string(year);
	date1.append("-");
	if (month < 10)
	{
		date1.append("0");
	}
	date2 = to_string(month);
	date2.append("-");
	if (day < 10)
	{
		date2.append("0");
	}
	date3 = to_string(day);
	date1.append(date2);
	date1.append(date3);
	return date1;
} 

void reverse(int kind) //��ԭ��˳�������Ҫ��תһ�� 1��ʾ��ת�û���0��Ʒ��-1����
{
	switch (kind)
	{
	case 1:
	{
		users* prev = NULL;
		users* curr = users_head;
		while (curr != NULL) {
			users* nextTemp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = nextTemp;
		}
		users_head = prev;
		break;
	}
	case 0:
	{
		goods* prev = NULL;
		goods* curr = goods_head;
		while (curr != NULL) {
			goods* nextTemp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = nextTemp;
		}
		goods_head = prev;
		break;
	}
	case -1:
	{
		orders* prev = NULL;
		orders* curr = orders_head;
		while (curr != NULL) {
			orders* nextTemp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = nextTemp;
		}
		orders_head = prev;
		break;
	}
	}
	
}

int search(const char str1[],const char str2[]) //ʵ��������Ʒ�Ĺ���
{
	bool judge = false;
	while (*str2!='\0')
	{
		while (*str1 != *str2 && *str2!='\0')
			str2++;
		while (*str1!='\0')
		{
			if (*str1 != *str2)
			{
				break;
			}
			str1++;
			str2++;
		}
		if (*str1 == '\0')
			judge = true;
	}
	if (judge)
		return 0;
	return -1;
	
}
void Init_View()  //��ʼ����
{
	system("cls");
	cout << "================================================================================" << endl;
	cout<<"��ӭ���붬�»����Ʒ����ϵͳ��"<<endl;
	cout << "1.�û���¼ 2.�û�ע�� 3.����Ա��¼ 4.�˳�����" << endl;
	cout << "================================================================================" << endl;
	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
}

bool judge_price(string price)//�ж�����ļ۸��Ƿ�Ϸ�
{
	int i=0;
	while (i<price.size()) 
	{
		if ((price[i]>'9' || price[i]<'0') && price[i]!='.')
			return false;//���ж��Ƿ��г������ֺ�С��������ķǷ��ַ�
		else if (price[i]=='.')
		{
			if (i+2!=price.size() || (price[i+1]>'9' && price[i+1]<'0'))	return false;
			//������С���㣬��������ֻ��һλ�ַ����ұ���������
		}
		i++;
	}
	return true;
}

bool judge_num(string num)
{
	int i=0;
	while (i<num.size())
	{
		if (num[i]>'9' || num[i]<'0')
			return false;
		i++;
	}
	return true;
}