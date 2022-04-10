#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
#include "seller.h"
#include "chatting.h"
extern bool bool_user, bool_admin;  //判断用户是否处于登录状态
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //初始定义了管理员账户
extern string admin_pwd ;
void seller_all_goods()
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
	cout << endl << endl << "您发布的商品如下："<<endl<<"****************************************************************************************************"<<endl;
	cout << "商品ID\t\t名称\t\t价格\t\t数量\t\t上架时间\t\t商品状态" << endl;
	goods* h = goods_head;
	vector<goods*> a;
	bool exist = false;
	while (h != NULL)
	{
		if (h->seller_id == current_user->id)
		{
			exist = true;
			a.push_back(h);
		}
		h = h->next;
	}
	sort(a.begin(),a.end(),cmp);//从大到小，降序
	if (key!=50)
	{
		for (int i=a.size()-1;i>=0;i--)
		{
			cout << left << a[i]->id << "\t\t" << setw(11) << a[i]->name << "\t" << a[i]->price << "\t\t" <<a[i]->num<<"\t\t"<< a[i]->on_shelf_time << "\t\t";
			if (a[i]->status == 1) cout << "销售中" << endl;
			if (a[i]->status == 0) cout << "已下架" << endl;
		}
	}
	else
	{
		for (int i=0;i<a.size();i++)
		{
			cout << left << a[i]->id << "\t\t" << setw(11) << a[i]->name << "\t" << a[i]->price << "\t\t" <<a[i]->num<<"\t\t"<< a[i]->on_shelf_time << "\t\t";
			if (a[i]->status == 1) cout << "销售中" << endl;
			if (a[i]->status == 0) cout << "已下架" << endl;
		}
	}
	if (exist == false)
		cout << "您还未发布任何商品！" << endl;
	cout << "****************************************************************************************************" << endl;
}
void seller_all_orders()
{
	orders* h = orders_head;
	cout << endl << "您的历史售出订单如下："<<endl;
	bool exist = false;
	cout << "****************************************************************************************************" << endl;
	cout << "订单ID\t\t商品ID\t\t单价\t\t数量\t\t交易时间\t\t买家ID" << endl;
	while (h != NULL)
	{
		if (h->seller_id == current_user->id)
		{
			exist = true;
			cout << h->id << "\t\t" << h->g_id << "\t\t" << h->amount << "\t\t" <<h->num<<"\t\t"<< h->time << "\t\t" << h->buyer_id << endl;
		}
		h = h->next;
	}
	if (exist == false)
	{
		cout << "暂无相关历史订单！" << endl;
	}
	cout<< "****************************************************************************************************" << endl;
}
void seller_remove_good(string id)
{
	goods* h = goods_head;
	bool exist = false;
	while (h != NULL)
	{
		if (h->id == id)
		{
			exist = true;
			if (h->seller_id == current_user->id)
			{
				cout << endl << "您确认要下架该商品吗？" << endl << endl << "******************************" << endl;
				cout << "商品ID：" << h->id << endl;
				cout << "商品名称：" << h->name << endl;
				cout << "商品价格：" << h->price << endl;
				cout << "商品数量：" << h->num << endl;
				cout << "上架时间：" << h->on_shelf_time << endl;
				cout << "商品描述：" << h->description << endl;
				cout << "******************************" << endl << endl << "请选择（y/n）：";
				cin.sync();
				int option = getchar();
				if (option == 121)
				{
					if (h->status == 1)
					{
						string exp=make_update("commodity","商品状态 = 已下架","商品ID",h->id);
						cout << endl << endl << "******************************" << endl;
						cout << "下架该商品成功！" << endl;
						h->status = 0;
						modify_file(0);
						break;
					}
					if (h->status == 0)
					{
						cout << endl << endl << "******************************" << endl;
						cout << "下架失败！该商品已为下架状态！" << endl;
						break;
					}
				}
				else
				{
					if (option == 110)
					{
						cout << endl << endl << "******************************" << endl;
						cout << "您已取消下架！" << endl;
						break;
					}
					else
					{
						cout << endl << endl << "******************************" << endl;
						cout << "下架失败！请输入y/n！" << endl;
						break;
					}
				}
			}
			else
			{
				cout << endl << endl << "******************************" << endl;
				cout <<"对不起！此商品并不是您发布的！您没有权限下架！" << endl<<endl;
				break;
			}
		}
		h = h->next;
	}
	if (exist == false)
	{
		cout << endl << endl << "******************************" << endl;
		cout << "下架失败！该商品ID不存在！" << endl;
	}
}
void seller_modify_good(int kind,string content,string id)
{
	goods* h=goods_head;
	while (h!=NULL)
	{
		if (h->id==id)
		{
			if (kind==1)//修改价格
			{
				h->price=stod(content);
				modify_file(0);
			}
			else if (kind==2)//修改描述
			{
				h->description=content;
				modify_file(0);
			}
			else
			{
				h->num=stoi(content);
				modify_file(0);
			}
			break;
		}
		h=h->next;
	}
}
void seller_publish_good(string content)
{
	string name,price,num,description,temp;
	for (int i=1;i<content.size()-1;i++)
	{
		if (content[i]==',')
		{
			if (name=="")	name=temp;
			else if (price=="")	price=temp;
			else if (num=="")	num=temp;
			temp="";
		}
		else
			temp+=content[i];
	}
	description=temp;
	goods_head->name=name;
	goods_head->price=stod(price);
	goods_head->num=stoi(num);
	goods_head->description=description;
	cout << endl << "发布商品成功！" << endl<<"******************************";
	goods_head->id = "M000";    //获取商品id
	if (goods_head->next != NULL)
		goods_head->number = goods_head->next->number + 1;
	else
		goods_head->number = 1;
	int number = goods_head->number, num_of_zero = 3;
	while (number > 0)
	{
		number /= 10;
		goods_head->id.pop_back();
	}
	goods_head->id.append(to_string(goods_head->number));
	goods_head->on_shelf_time = get_time();
	goods_head->seller_id = current_user->id;
	goods_head->status = 1;
	modify_file(0);
}

void seller_View()
{
	cout << "==============================================================================================================" << endl;
	cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.联系其他用户 7.返回用户主界面 8.清屏" << endl;
	cout << "==============================================================================================================" << endl;
	if (current_user->message!="")	cout<<"-----注意！有新的消息！-----"<<endl;
	cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
}
void seller() //卖家界面
{
	system("cls");
	seller_View();
	cin.sync();
	int key = getchar();
	while (key != 55)
	{
		switch (key)
		{
		case 49:
		{
			goods* newone = new goods;
			cout << endl << endl << "请输入商品名称：";
			cin.sync();
			getline(cin,newone->name);
			cout << "请输入商品价格：";
			string temp;
			while (1) // 判断输入的价格是否合法
			{
				cin.sync();
				getline(cin,temp);
				if (judge_price(temp))
					break;
				else
				{
					cout<<endl<<"-----输入无效！请重新输入！-----"<<endl<<endl;
					cout << "请输入商品价格：";
				}
			}
			newone->price=stod(temp);
			cout<<"请输入商品数量：";
			while (1) //判断数量的合法性
			{
				cin.sync();
				getline(cin,temp);
				if (judge_num(temp))
					break;
				else
				{
					cout<<endl<<"-----输入无效！请重新输入！-----"<<endl<<endl;
					cout << "请输入商品数量：";
				}
			}
			newone->num=stoi(temp);
			cout << "请输入商品描述：";
			cin.sync();
			getline(cin,newone->description);
			cout << endl << endl << "请确认输入的商品信息无误：" << endl << "******************************" << endl;
			cout << "商品名称：" << newone->name << endl << "商品价格：" << newone->price << endl <<"商品数量："<<newone->num<<endl<< "商品描述：" << newone->description << endl;
			cout << "******************************" << endl << endl << "您确认要发布此商品吗（y/n）:";
			cin.sync();
			int option = getchar();
			if (option == 121)
			{
				string price=to_string(newone->price);
				for (int i=1;i<=5;i++)	price.pop_back();
				string exp=make_insert("commodity","("+newone->name+","+price+","+to_string(newone->num)+","+newone->description+")");
				newone->next = goods_head;
				goods_head = newone;
				analyse_sql(exp,-1);
			}
			else
			{
				if (option == 110)
				{
					cout << endl << "-----取消发布该商品！-----" << endl;
				}
				else
				{
					cout << endl << "-----发布商品失败！请输入y或n！-----" << endl;
				}
			}
			cout << endl<<endl;
			seller_View();
			break;
		}
		case 50:
		{
			string exp=make_select("commodity","","");
			analyse_sql(exp,-1);
			cout<<endl<<endl;
			seller_View();
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 51:
		{
			cout << endl << "************************************************************" << endl;
			cout << "请输入想要修改的商品ID：";
			string id;
			cin.sync();
			getline(cin,id);
			bool exist = false;
			goods* h = goods_head;
			while (h != NULL)
			{
				if (h->id == id)
				{
					exist=true;
					if (h->seller_id!=current_user->id)
					{
						cout<<endl<<"对不起！此商品并非您所发布的商品，您无权修改！"<<endl;
						break;
					}
					cout << "请输入要修改的信息（1.价格 2.商品描述）：";
					cin.sync();
					int option = getchar();
					switch (option)
					{
					case 49:
					{
						cout << "请输入修改后的商品价格：";
						string price;
						while (1) // 判断输入的价格是否合法
						{
							cin.sync();
							getline(cin,price);
							if (judge_price(price))
								break;
							else
							{
								cout<<endl<<"-----输入无效！请重新输入！-----"<<endl<<endl;
								cout << "请输入修改后的商品价格：";
							}
						}
						cout << endl << "请确认修改后的商品信息："<<endl;
						cout << endl << "****************************************" << endl;
						cout << "商品ID:" << h->id << endl;
						cout << "商品名称：" << h->name << endl;
						cout << "商品价格：" << price <<"元" << endl;
						cout << "商品描述：" << h->description << endl;
						cout << "****************************************" << endl;
						cout << endl<<"确认修改？(y/n)：" ;
						cin.sync();
						int o = getchar();
						switch (o)
						{
						case 121:
						{
							cout << endl << "-----修改成功！-----" <<endl<< endl << "************************************************************" << endl;
							price=to_string(stod(price));
							for (int i=1;i<=5;i++)	price.pop_back();
							string exp=make_update("commodity","价格 = "+price,"商品ID",h->id);
							analyse_sql(exp,-1);
						/*	h->price = stod(price);
							modify_file(0);
						*/	break;
						}
						case 110:
						{
							cout << endl << "-----取消修改！-----"<<endl << endl << "************************************************************" << endl;
							break;
						}
						default:
							cout << endl << "-----修改失败！请输入y/n！-----" <<endl<< endl << "************************************************************" << endl;
							break;
						}
						break;
					}
					case 50:
					{
						cout  << "请输入修改后的商品描述：";
						string d;
						cin.sync();
						getline(cin,d);
						cout << endl << "请确认修改后的商品信息：" << endl;
						cout << endl << "****************************************" << endl;
						cout << "商品ID:" << h->id << endl;
						cout << "商品名称：" << h->name << endl;
						cout << "商品价格：" << h->price << "元" << endl;
						cout << "商品描述：" << d << endl;
						cout << "****************************************" << endl;
						cout <<endl<< "确认修改？(y/n)：";
						cin.sync();
						int o = getchar();
						switch (o)
						{
						case 121:
						{
							cout << endl << "-----修改成功！-----"<<endl << endl << "************************************************************" << endl;
							string exp=make_update("commodity","描述 = "+d,"商品ID",h->id);
							analyse_sql(exp,-1);
						/*	h->description=d;
							modify_file(0);
						*/	break;
						}
						case 110:
						{
							cout << endl << "-----取消修改！-----" << endl<<endl << "************************************************************" << endl;
							break;
						}
						default:
							cout << endl << "-----修改失败！请输入y/n！-----" <<endl<< endl << "************************************************************" << endl;
							break;
						}
						break;

					}
					default:
						cout << endl << "-----没有对应的商品属性！修改失败！-----" <<endl<<endl<< "************************************************************" << endl;
						break;
					}
					break;
				}
				h = h->next;
			}
			if (exist == false)
			{
				cout << endl << "您输入的商品ID不存在！" << endl;
				cout << "************************************************************" << endl;
			}
			cout << endl<<endl;
			seller_View();
			break;
		}
		case 52://下架商品
		{
			cout << endl << "******************************" << endl;
			cout << "请输入你要下架的商品的ID：";
			string id;
			cin.sync();
			getline(cin,id);
			string exp=make_update("commodity","商品状态 = 已下架","商品ID",id);
			analyse_sql(exp,-1);
			cout<<endl<<endl;
			seller_View();
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 53://查看历史订单
		{
			string exp=make_select("order","","");
			analyse_sql(exp,-1);
			cout<<endl<<endl;
			seller_View();
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 54:
		{
			chat_with_other();
			cout << endl<<endl<<"请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		case 56:
		{
			system("cls");
			seller_View();
			break;
		}
		default:
			cout<<endl<<"-----输入无效！请重新输入！-----"<<endl;
			cout << "请输入操作(第一个字符有效，多余视为无效输入)：";
			break;
		}
		cin.sync();
		key = getchar();
	}
	personal_menu();
}