#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
#include "admin.h"
extern bool bool_user, bool_admin;  //判断用户是否处于登录状态
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //初始定义了管理员账户
extern string admin_pwd ;
void admin_all_goods()
{
	cout << endl << endl << "*******************************************************************************************************************" << endl;
	cout << "ID\t\t名称\t\t价格\t\t上架时间\t\t卖家id\t\t数量\t\t商品状态" << endl;
	goods* h = goods_head;
	while (h != NULL)
	{
		cout << left;
		cout << h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" << h->on_shelf_time << "\t\t" << h->seller_id <<"\t\t"<<h->num<<"\t\t";
		if (h->status == 1) cout << "销售中" << endl;
		if (h->status == 0) cout << "已下架" << endl;
		h = h->next;
	}
	cout << "*******************************************************************************************************************" << endl;
}
void admin_search_good(string name)
{
	cout << endl << endl << "*******************************************************************************************************************" << endl;
	cout << "ID\t\t名称\t\t价格\t\t上架时间\t\t卖家id\t\t数量\t\t商品状态" << endl;
	bool j = false;//判断是否存在该商品
	goods* h = goods_head;
	while (h != NULL)
	{
		if (h->name.size()>=name.size())
		{
			if (search(name.c_str(), h->name.c_str()) == 0)
			{
				cout << left;
				cout << h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" << h->on_shelf_time << "\t\t" << h->seller_id << "\t\t"<<h->num<<"\t\t";
				j = true;
				if (h->status == 1) cout << "销售中" << endl;
				if (h->status == 0) cout << "已下架" << endl;
			}
		}
		h = h->next;
	}
	if (j == false)
		cout << "-----对不起！无法搜索到此商品！-----" << endl;
	cout << "*******************************************************************************************************************" << endl;
}
void admin_all_orders()
{
	orders* h = orders_head;
	cout << endl << "**********************************************************************" << endl;
	cout << "订单id\t商品id\t单价\t数量\t交易时间\t卖家id\t" << endl;
	while (h != NULL)
	{
		cout << h->id << "\t" << h->g_id << "\t" << h->amount << "\t" <<h->num<<"\t"<< h->time << "\t" << h->seller_id << endl;
		h = h->next;
	}
	cout << "**********************************************************************" << endl;
}
void admin_all_users()
{
	users* h = users_head;
	cout << endl << "*******************************************************************************************************************" << endl;
	cout << "用户ID\t\t用户名\t\t联系方式\t地址\t\t\t余额\t\t用户状态"<<endl;
	while (h != NULL)
	{
		cout << left << h->id << "\t\t" << setw(11) << h->name << "\t" << h->contact << "\t" << setw(21) << h->address << "\t" << h->money<<"\t\t";
		if (h->status)	cout<<"正常"<<endl;	else	cout<<"封禁"<<endl;
		h = h->next;
	}
	cout<< "*******************************************************************************************************************" << endl;
}
void admin_remove_good(string id)
{
	goods* h = goods_head;
	bool exist = false;
	while (h != NULL)
	{
		if (h->id == id)
		{
			exist = true;
			cout << endl << "-----您确认要下架该商品吗？-----"<<endl<<endl<<"******************************"<<endl;
			cout << "商品ID：" << h->id << endl;
			cout << "商品名称：" << h->name << endl;
			cout << "商品价格：" << h->price << endl;
			cout<<"商品数量："<<h->num<<endl;
			cout<<"上架时间："<<h->on_shelf_time<<endl;
			cout << "商品描述：" << h->description << endl;
			cout << "******************************" << endl << endl << "请选择（y/n）：";
			cin.sync();
			int option = getchar();
			if (option == 121)
			{
				if (h->status == 1)
				{
					cout << endl << endl << "******************************" << endl;
					cout << "-----下架该商品成功！-----" << endl;
					h->status = -1;
					modify_file(0);
					break;
				}
				if (h->status == 0)
				{
					cout << endl << endl << "******************************" << endl;
					cout << "-----下架失败！该商品已为下架状态！-----" << endl;
					break;
				}
			}
			else
			{
				if (option == 110)
				{
					cout << endl << endl << "******************************" << endl;
					cout << "-----您已取消下架！-----" << endl;
					break;
				}
				else
				{
					cout << endl << endl << "******************************" << endl;
					cout << "-----下架失败！请输入y/n！-----" << endl;
					break;
				}
			}
		}
		h = h->next;
	}
	if (exist == false)
	{
		cout<< endl << endl << "******************************" << endl;
		cout << "-----下架失败！该商品ID不存在！-----" << endl;
	}
}
void admin_ban_user(string id)
{
	users* curr = users_head;
	bool exist = false; //判断此id是否存在
	bool judge=false;//判断封禁是否成功
	while (curr != NULL)
	{
		if (curr->id == id)
		{
			exist = true;
			cout << endl << "-----您确认要封禁该用户吗？-----" << endl << endl << "*************************" << endl;
			cout << "用户ID：" << curr->id << endl;
			cout << "用户名：" << curr->name << endl;
			cout << "联系方式：" << curr->contact << endl;
			cout<<"用户地址："<<curr->address<<endl;
			cout<<"钱包余额："<<curr->money<<endl;
			cout << "*************************" << endl << endl << "请选择（y/n）：";
			cin.sync();
			int option = getchar();
			if (option == 121)
			{
				cout << endl << endl << "***********************************" << endl;
				cout << "-----封禁用户成功！-----" << endl;
				curr->status=false;
				judge=true;
				modify_file(1);
			}
			else
			{
				if (option == 110)
				{
					cout << endl << endl << "***********************************" << endl;
					cout << "-----您已取消封禁！-----" << endl;
				}
				else
				{
					cout << endl << endl << "***********************************" << endl;
					cout << "-----封禁失败！请输入y/n！-----" << endl;
				}
			}
			break;
		}
		curr = curr->next;
	}
	if (exist==false)
	{
		cout << endl << endl << "***********************************" << endl<<endl;
		cout << "-----封禁用户失败！用户ID不存在！-----" << endl;
	}
	if (judge)
	{
		goods* h=goods_head;
		while (h!=NULL)
		{
			if (h->seller_id==curr->id)
			{
				string exp=make_update("commodity","商品状态 = 已下架","卖家ID",h->seller_id);
				h->status=false;
				modify_file(0);
			}
			h=h->next;
		}
	}
}

void admin_menu() //管理员界面
{
	system("cls");
	cout << "================================================================================" << endl;
	cout << "1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.封禁用户 6.下架商品 7.注销" << endl;
	cout << "================================================================================" << endl;
	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
	cin.sync();
	int key = getchar();
	while (key != 55)
	{
		switch (key)
		{
		case 49:
		{
			string exp=make_select("commodity","","");
			analyse_sql(exp,1);
		/*	cout << endl << endl << "*******************************************************************************************************************" << endl;
			cout << "ID\t\t名称\t\t价格\t\t上架时间\t\t卖家id\t\t数量\t\t商品状态" << endl;
			goods* h = goods_head;
			while (h != NULL)
			{
				cout << left;
				cout << h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" << h->on_shelf_time << "\t\t" << h->seller_id <<"\t\t"<<h->num<<"\t\t";
				if (h->status == 1) cout << "销售中" << endl;
				if (h->status == 0) cout << "已下架" << endl;
				h = h->next;
			}
			cout << "*******************************************************************************************************************" << endl;
		*/	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 50:
		{
			cout << endl << "请输入要搜索的名称：";
			string name;
			cin.sync();
			getline(cin,name);
			string exp=make_select("commodity","名称",name);
			analyse_sql(exp,1);
		/*	cout << endl << endl << "*******************************************************************************************************************" << endl;
			cout << "ID\t\t名称\t\t价格\t\t上架时间\t\t卖家id\t\t数量\t\t商品状态" << endl;
			bool j = false;//判断是否存在该商品
			goods* h = goods_head;
			while (h != NULL)
			{
				if (h->name.size()>=name.size())
				{
					if (search(name.c_str(), h->name.c_str()) == 0)
					{
						cout << left;
						cout << h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" << h->on_shelf_time << "\t\t" << h->seller_id << "\t\t"<<h->num<<"\t\t";
						j = true;
						if (h->status == 1) cout << "销售中" << endl;
						if (h->status == 0) cout << "已下架" << endl;
					}
				}
				h = h->next;
			}
			if (j == false)
				cout << "-----对不起！无法搜索到此商品！-----" << endl;
			cout << "*******************************************************************************************************************" << endl;
		*/	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 51:
		{
			string exp=make_select("order","","");
			analyse_sql(exp,1);
		/*	orders* h = orders_head;
			cout << endl << "**********************************************************************" << endl;
			cout << "订单id\t商品id\t单价\t数量\t交易时间\t卖家id\t" << endl;
			while (h != NULL)
			{
				cout << h->id << "\t" << h->g_id << "\t" << h->amount << "\t" <<h->num<<"\t"<< h->time << "\t" << h->seller_id << endl;
				h = h->next;
			}
			cout << "**********************************************************************" << endl;
		*/	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 52:
		{
			string exp=make_select("user","","");
			analyse_sql(exp,1);
		/*	users* h = users_head;
			cout << endl << "*******************************************************************************************************************" << endl;
			cout << "用户ID\t\t用户名\t\t联系方式\t地址\t\t\t余额\t\t用户状态"<<endl;
			while (h != NULL)
			{
				cout << left << h->id << "\t\t" << setw(11) << h->name << "\t" << h->contact << "\t" << setw(21) << h->address << "\t" << h->money<<"\t\t";
				if (h->status)	cout<<"正常"<<endl;	else	cout<<"封禁"<<endl;
				h = h->next;
			}
			cout<< "*******************************************************************************************************************" << endl;
		*/	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 53:
		{
			cout << endl << "请输入你要封禁的用户ID：";
			string id;
			cin.sync();
			getline(cin,id);
			string exp1=make_update("user","用户状态 = 封禁","用户ID",id);
			analyse_sql(exp1,1);
		/*	users* prev = NULL;
			users* curr = users_head;
			bool exist = false; //判断此id是否存在
			bool judge=false;//判断封禁是否成功
			while (curr != NULL)
			{
				if (curr->id == id)
				{
					exist = true;
					cout << endl << "-----您确认要封禁该用户吗？-----" << endl << endl << "*************************" << endl;
					cout << "用户ID：" << curr->id << endl;
					cout << "用户名：" << curr->name << endl;
					cout << "联系方式：" << curr->contact << endl;
					cout<<"用户地址："<<curr->address<<endl;
					cout<<"钱包余额："<<curr->money<<endl;
					cout << "*************************" << endl << endl << "请选择（y/n）：";
					cin.sync();
					int option = getchar();
					if (option == 121)
					{
						if (prev == NULL)
						{
							users_head = curr->next;
							delete curr;
							cout << endl << endl << "***********************************" << endl;
							cout << "-----封禁用户成功！-----" << endl;
							judge=true;
							modify_file(1);
						}
						else
						{
							prev->next = curr->next;
							delete curr;
							cout << endl << endl << "***********************************" << endl;
							cout << "-----封禁用户成功！-----" << endl;
							judge=true;
							modify_file(1);
						}
					}
					else
					{
						if (option == 110)
						{
							cout << endl << endl << "***********************************" << endl;
							cout << "-----您已取消封禁！-----" << endl;
						}
						else
						{
							cout << endl << endl << "***********************************" << endl;
							cout << "-----封禁失败！请输入y/n！-----" << endl;
						}
					}
					break;
				}
				prev = curr;
				curr = curr->next;
			}
			if (exist==false)
			{
				cout << endl << endl << "***********************************" << endl;
				cout << "-----封禁用户失败！用户ID不存在！-----" << endl;
			}
			if (judge)
			{
				goods* h=goods_head;
				while (h!=NULL)
				{
					if (h->seller_id==curr->id)
					{
						string exp2=make_update("commodity","商品状态 = 已下架","卖家ID",h->seller_id);
						h->status=false;
						modify_file(0);
						break;
					}
				}
			}
		*/	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 54:
		{
			cout << endl << "******************************" << endl;
			cout << "请输入你要下架的商品的ID：";
			string id;
			cin.sync();
			getline(cin,id);
			string exp=make_update("commodity","商品状态 = 已下架","商品ID",id);
			analyse_sql(exp,1);
		/*	goods* h = goods_head;
			bool exist = false;
			while (h != NULL)
			{
				if (h->id == id)
				{
					exist = true;
					cout << endl << "-----您确认要下架该商品吗？-----"<<endl<<endl<<"******************************"<<endl;
					cout << "商品ID：" << h->id << endl;
					cout << "商品名称：" << h->name << endl;
					cout << "商品价格：" << h->price << endl;
					cout<<"商品数量："<<h->num<<endl;
					cout<<"上架时间："<<h->on_shelf_time<<endl;
					cout << "商品描述：" << h->description << endl;
					cout << "******************************" << endl << endl << "请选择（y/n）：";
					cin.sync();
					int option = getchar();
					if (option == 121)
					{
						if (h->status == 1)
						{
							cout << endl << endl << "******************************" << endl;
							cout << "-----下架该商品成功！-----" << endl;
							h->status = -1;
							modify_file(0);
							break;
						}
						if (h->status == 0)
						{
							cout << endl << endl << "******************************" << endl;
							cout << "-----下架失败！该商品已为下架状态！-----" << endl;
							break;
						}
					}
					else
					{
						if (option == 110)
						{
							cout << endl << endl << "******************************" << endl;
							cout << "-----您已取消下架！-----" << endl;
							break;
						}
						else
						{
							cout << endl << endl << "******************************" << endl;
							cout << "-----下架失败！请输入y/n！-----" << endl;
							break;
						}
					}
				}
				h = h->next;
			}
			if (exist == false)
			{
				cout<< endl << endl << "******************************" << endl;
				cout << "-----下架失败！该商品ID不存在！-----" << endl;
			}
		*/	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		default:
			cout<<endl<<"-----无效输入！请重新输入！-----"<<endl;
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
		}
		cin.sync();
		key = getchar();
	}
	bool_admin = false;
	cout << endl << "***************注销成功！按任意键返回主界面。***************" << endl;
	cin.sync();
	getchar();
	Init_View();
}