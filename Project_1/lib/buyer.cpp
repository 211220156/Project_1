#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
#include "buyer.h"
#include "chatting.h"
extern bool bool_user, bool_admin;  //判断用户是否处于登录状态
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //初始定义了管理员账户
extern string admin_pwd ;
void buyer_all_goods()
{
	cout<<"您想按价格升序还是降序？(1.升序 2.降序)：";
	cin.sync();
	int key=getchar();
	switch (key)
	{
		case 49:
		{
			cout<<endl<<"商品将按价格升序排序：";
			break;
		}
		case 50:
		{
			cout<<endl<<"商品将按价格降序排序：";
			break;
		}
		default:
			cout<<"输入非法！将按默认升序排序：";
	}
	cout << endl << endl << "**************************************************************************************************************" << endl;
	cout << "ID\t\t名称\t\t价格\t\t数量\t\t上架时间\t\t卖家id\t\t" << endl;
	goods* h = goods_head;
	vector<goods*> a;
	while (h != NULL)
	{
		if (h->status == 1)
			a.push_back(h);
		//	cout <<left<< h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" <<h->num<<"\t\t"<< h->on_shelf_time << "\t\t" << h->seller_id << endl;
		h = h->next;
	}
	sort(a.begin(),a.end(),cmp); //从大到小，降序
	if (key!=50)
	{
		for (int i=a.size()-1;i>=0;i--)
			cout <<left<< a[i]->id << "\t\t" << setw(11)<<a[i]->name << "\t" << a[i]->price << "\t\t" <<a[i]->num<<"\t\t"<< a[i]->on_shelf_time << "\t\t" << a[i]->seller_id << endl;
	}
	else
	{
		for (int i=0;i<a.size();i++)
			cout <<left<< a[i]->id << "\t\t" << setw(11)<<a[i]->name << "\t" << a[i]->price << "\t\t" <<a[i]->num<<"\t\t"<< a[i]->on_shelf_time << "\t\t" << a[i]->seller_id << endl;
	}
	cout << "**************************************************************************************************************" << endl<<endl<<endl;
	buyer_View();
}
void buyer_search_good(string name)
{
	cout << endl << endl << "****************************************************************************************************" << endl;
	cout << "ID\t\t名称\t\t价格\t\t上架时间\t\t卖家id\t\t商品状态\t\t" << endl;
	bool j = false;//判断是否存在该商品
	goods* h = goods_head;
	while (h != NULL)
	{
		if (h->name.size()>=name.size())
		{
			if (search(name.c_str(), h->name.c_str()) == 0 && h->status==1)
			{
				cout << left<<h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" << h->on_shelf_time << "\t\t" << h->seller_id<<"\t\t"<<"销售中"<<endl;
				j = true;
			}
		}
		h = h->next;
	}
	if (j == false)
		cout << "-----对不起！无法搜索到此商品！-----" << endl;
	cout<< "****************************************************************************************************" << endl;
	cout << endl<<endl<<endl;
	buyer_View();	
}
void buyer_all_orders()
{
	orders* h = orders_head;
	bool judge_empty = false;//判断是否有订单。
	cout << endl << "**********************************************************************" << endl;
	cout << "订单id\t商品id\t金额\t交易时间\t卖家id\t" << endl;
	while (h != NULL)
	{
		if (h->buyer_id==current_user->id)
		{
			judge_empty = true;
			cout << h->id << "\t" << h->g_id << "\t" << h->amount << "\t" << h->time << "\t" << h->seller_id << endl;
		}
		h = h->next;
	}
	if (judge_empty==false)
	{
		cout << "无相关订单记录！" << endl;
	}
	cout << "**********************************************************************" << endl;
	cout <<endl<<endl<<endl;
	buyer_View();	
}
void buyer_good_details(string id)
{
	cout << endl << "**********************************************************************" << endl;
	bool judge_exist = false;//判断商品id是否存在
	goods* h = goods_head;
	while (h != NULL)
	{
		if (h->id==id)
		{
			judge_exist = true;
			cout << "商品名称：      " << h->name << endl;
			cout << "商品描述：      " << h->description << endl;
			cout << "商品价格：      " << h->price<<endl;
			cout << "上架时间:       " << h->on_shelf_time << endl;
			cout << "卖家id：        " << h->seller_id << endl;
			cout << "商品状态：      " ;
			switch (h->status)
			{
			case 1:
			{
				cout << "销售中" << endl;
				break;
			}
			case 0:
			{
				cout << "已下架" << endl;
				break;
			}
			}
			break;
		}
		h = h->next;
	}
	if (judge_exist == false)
	{
		cout << "-----您输入的商品id不存在！-----" << endl;
	}
	cout<< "**********************************************************************" << endl;
	cout <<endl<<endl<<endl;
	buyer_View();	
}
void buyer_purchase_good(string content)
{
	string id,g_id,amount,num,time,seller_id,buyer_id,temp;
	for (int i=1;i<content.size()-1;i++)
	{
		if (content[i]==',')
		{
			if (id=="")	id=temp;
			else if (g_id=="")	g_id=temp;
			else if (amount=="")	amount=temp;
			else if (num=="")	num=temp;
			else if (time=="")	time=temp;
			else if (seller_id=="")	seller_id=temp;
			temp="";
		}
		else
			temp+=content[i];
	}
	buyer_id=temp;
	orders_head->id=id;
	orders_head->amount=stod(amount);
	orders_head->time = time;//获取交易时间
	orders_head->num=stoi(num);
	orders_head->buyer_id = buyer_id;
	orders_head->g_id = g_id;
	orders_head->seller_id= seller_id;
	modify_file(1);
	modify_file(0);
	modify_file(-1);
}
void buyer_remove_good(string id)//用于买东西时将东西买完的情况。
{
	goods* h=goods_head;
	while (h!=NULL)
	{
		if (h->id==id)
		{
			h->status=false;
			break;
		}
		h=h->next;
	}
}
void buyer_View()
{
	cout << "===============================================================================================================" << endl;
	cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.联系其他用户 7.返回用户主界面 8.清屏" << endl;
	cout << "===============================================================================================================" << endl;
	if (current_user->message!="")	cout<<"-----注意！有新的消息！-----"<<endl;
	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
}
void buyer()  //买家界面
{
	system("cls");
	buyer_View();
	cin.sync();
	int key = getchar();
	while (key != 55)
	{
		switch (key)
		{
		case 49:
		{
			string exp=make_select("commodity","","");
			analyse_sql(exp,0);
			break;
		}
		case 50:
		{
			cout << endl << "请输入商品id:";
			string id;
			cin.sync();
			getline(cin,id);
			int num,i=0;
			bool judge_num=true;//判断输入的数量是否合法。
			string str;
			cout<<"请输入数量：";
			while (1)
			{
				i=0;
				cin.sync();
				getline(cin,str);
				judge_num=true;
				while (i<str.size())
				{
					if (str[i]<'0' || str[i]>'9')
					{
						judge_num=false;
						cout<<endl<<"-----输入有误！请重新输入！-----"<<endl;
						cout<<"请输入数量：";
						break;
					}
					i++;
				}
				if (judge_num) break;
			}
			num=stoi(str);
			bool judge = 0;//判断交易是否成功
			goods* h = goods_head;
			while (h != NULL)
			{
				if (h->id==id)
				{
					judge = 1;
					break;
				}
				h = h->next;
			}
			if (judge == 1)
			{
				if (h->num>=num)
				{
					if (current_user->money >= h->price*num)
					{
						//current_user->money -= h->price*num;
						string exp1=make_update("commodity","数量 = "+to_string(h->num-num),"商品ID",h->id);
						analyse_sql(exp1,0);
						if (h->num-num==0)
						{
							string exp3=make_update("commodity","商品状态 = 已下架","商品ID",h->id);
							analyse_sql(exp3,0);
						}
						string price=to_string(h->price);
						for (int i=1;i<=5;i++)	price.pop_back();
						current_user->money_exp+=("-"+to_string(num)+"*"+price);//生成表达式
						current_user->money=stod(calculator(current_user->money_exp));//通过表达式计算余额。
						users* seller=users_head;
						while (seller!=NULL) //卖出了商品，卖家钱会增加。
						{
							if (seller->id==h->seller_id)
							{
								seller->money_exp+=("+"+to_string(num)+"*"+price);
								seller->money=stod(calculator(seller->money_exp));
								break;
							}
							seller=seller->next;
						}
						h->num-=num;
						if (h->num==0)	h->status=0;
						cout << endl << "******************************" << endl << "交易提醒！" << endl << "交易时间：";
						orders* newone = new orders;
						newone->id = "T000";    //获取订单号
						if (orders_head != NULL)
							newone->number = orders_head->number + 1;
						else
							newone->number = 1;
						int number = newone->number;
						while (number > 0)
						{
							number /= 10;
							newone->id.pop_back();
						}
						newone->id.append(to_string(newone->number));
						string amount=to_string(h->price);
						for (int i=1;i<=5;i++)	amount.pop_back();
						string exp2=make_insert("order","("+newone->id+","+h->id+","+amount+","+to_string(num)+","+get_time()+","+h->seller_id+","+current_user->id+")");
						newone->next = orders_head;
						orders_head = newone;
						analyse_sql(exp2,0);
						cout << newone->time<<endl<<"交易单价："<<h->price<<endl<<"交易数量："<<num<<endl<<"交易状态：成功"<<endl<<"账户余额："<<current_user->money;
						cout << endl << "******************************"<<endl;
					}
					else
					{
						cout << endl << "******************************" << endl << "交易失败！" ;
						cout << endl << "您的余额不足！" << endl<<"******************************";
					}
				}
				else
				{
					cout << endl << "******************************" << endl << "交易失败！" ;
					cout << endl << "商品存货不足！" << endl<<"******************************";
				}
			}
			else
			{
				cout << endl << "******************************" << endl << "交易失败！" ;
				cout << endl << "商品id不存在！" << endl << "******************************"<<endl;
			}
			cout << endl<<endl<<endl;
			buyer_View();
			break;
		}
		case 51:
		{
			cout << endl << "请输入要搜索的名称：";
			string name;
			cin.sync();
			getline(cin,name);
			string exp=make_select("commodity","名称",name);
			analyse_sql(exp,0);
			break;
		}
		case 52:
		{
			
			string exp=make_select("order","","");
			analyse_sql(exp,0);
			break;
		}
		case 53:
		{
			cout << endl << "请输入你想查看的商品ID：";
			string id;
			cin.sync();
			getline(cin,id);
			string exp=make_select("commodity","商品ID",id);
			analyse_sql(exp,0);
			break;
		}
		case 54:
		{
			chat_with_other();
			cout << endl<<endl<<endl;
			buyer_View();
			break;
		}
		case 56:
		{
			system("cls");
			buyer_View();
			break;
		}
		default:
			cout<<endl<<"-----无效输入！请重新输入！-----"<<endl;
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
		}
		cin.sync();
		key = getchar();
	}
	cout<<endl<<endl<<"**********按任意键返回主菜单！**********"<<endl;
	cin.sync();
	getchar();
	personal_menu();
}