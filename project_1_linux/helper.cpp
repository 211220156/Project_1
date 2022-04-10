#include "trading_platform.h"
#include "calculator.h"
extern bool bool_user, bool_admin;  //判断用户是否处于登录状态
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //初始定义了管理员账户
extern string admin_pwd ;
string get_time()//用于获取交易的时间
{
	time_t rawtime = time(0);
	struct tm localtm = *localtime(&rawtime);//转换为tm struct
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

void reverse(int kind) //按原先顺序输出，要反转一次 1表示反转用户，0商品，-1订单
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

int search(const char str1[],const char str2[]) //实现搜索商品的功能
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
void Init_View()  //初始界面
{
	system("clear");
	cout << "================================================================================" << endl;
	cout<<"欢迎进入冬奥会纪念品交易系统！"<<endl;
	cout << "1.用户登录 2.用户注册 3.管理员登录 4.退出程序" << endl;
	cout << "================================================================================" << endl;
	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
}

bool judge_price(string price)//判断输入的价格是否合法
{
	int i=0;
	while (i<price.size()) 
	{
		if ((price[i]>'9' || price[i]<'0') && price[i]!='.')
			return false;//先判断是否有除了数字和小数点以外的非法字符
		else if (price[i]=='.')
		{
			if (i+2!=price.size() || (price[i+1]>'9' && price[i+1]<'0'))	return false;
			//若遇到小数点，则后面必须只有一位字符，且必须是数字
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

string get_accurate_time()
{
	time_t rawtime = time(0);
	struct tm localtm = *localtime(&rawtime);//转换为tm struct
	int year = localtm.tm_year + 1900;
	int month = localtm.tm_mon + 1;
	int day = localtm.tm_mday;
    int hour = localtm.tm_hour;
    int min = localtm.tm_min;
    int sec = localtm.tm_sec;
    string h,m,s;
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
    if (hour<10)    h="0"+to_string(hour); else h=to_string(hour);
    if (min<10)    m="0"+to_string(min); else m=to_string(min);
    if (sec<10)    s="0"+to_string(sec); else s=to_string(sec);
    date1.append(" "+h+":"+m+":"+s);
	return date1;
}
