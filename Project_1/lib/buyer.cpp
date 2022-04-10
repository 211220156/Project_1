#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
#include "buyer.h"
#include "chatting.h"
extern bool bool_user, bool_admin;  //�ж��û��Ƿ��ڵ�¼״̬
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //��ʼ�����˹���Ա�˻�
extern string admin_pwd ;
void buyer_all_goods()
{
	cout<<"���밴�۸������ǽ���(1.���� 2.����)��";
	cin.sync();
	int key=getchar();
	switch (key)
	{
		case 49:
		{
			cout<<endl<<"��Ʒ�����۸���������";
			break;
		}
		case 50:
		{
			cout<<endl<<"��Ʒ�����۸�������";
			break;
		}
		default:
			cout<<"����Ƿ�������Ĭ����������";
	}
	cout << endl << endl << "**************************************************************************************************************" << endl;
	cout << "ID\t\t����\t\t�۸�\t\t����\t\t�ϼ�ʱ��\t\t����id\t\t" << endl;
	goods* h = goods_head;
	vector<goods*> a;
	while (h != NULL)
	{
		if (h->status == 1)
			a.push_back(h);
		//	cout <<left<< h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" <<h->num<<"\t\t"<< h->on_shelf_time << "\t\t" << h->seller_id << endl;
		h = h->next;
	}
	sort(a.begin(),a.end(),cmp); //�Ӵ�С������
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
	cout << "ID\t\t����\t\t�۸�\t\t�ϼ�ʱ��\t\t����id\t\t��Ʒ״̬\t\t" << endl;
	bool j = false;//�ж��Ƿ���ڸ���Ʒ
	goods* h = goods_head;
	while (h != NULL)
	{
		if (h->name.size()>=name.size())
		{
			if (search(name.c_str(), h->name.c_str()) == 0 && h->status==1)
			{
				cout << left<<h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" << h->on_shelf_time << "\t\t" << h->seller_id<<"\t\t"<<"������"<<endl;
				j = true;
			}
		}
		h = h->next;
	}
	if (j == false)
		cout << "-----�Բ����޷�����������Ʒ��-----" << endl;
	cout<< "****************************************************************************************************" << endl;
	cout << endl<<endl<<endl;
	buyer_View();	
}
void buyer_all_orders()
{
	orders* h = orders_head;
	bool judge_empty = false;//�ж��Ƿ��ж�����
	cout << endl << "**********************************************************************" << endl;
	cout << "����id\t��Ʒid\t���\t����ʱ��\t����id\t" << endl;
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
		cout << "����ض�����¼��" << endl;
	}
	cout << "**********************************************************************" << endl;
	cout <<endl<<endl<<endl;
	buyer_View();	
}
void buyer_good_details(string id)
{
	cout << endl << "**********************************************************************" << endl;
	bool judge_exist = false;//�ж���Ʒid�Ƿ����
	goods* h = goods_head;
	while (h != NULL)
	{
		if (h->id==id)
		{
			judge_exist = true;
			cout << "��Ʒ���ƣ�      " << h->name << endl;
			cout << "��Ʒ������      " << h->description << endl;
			cout << "��Ʒ�۸�      " << h->price<<endl;
			cout << "�ϼ�ʱ��:       " << h->on_shelf_time << endl;
			cout << "����id��        " << h->seller_id << endl;
			cout << "��Ʒ״̬��      " ;
			switch (h->status)
			{
			case 1:
			{
				cout << "������" << endl;
				break;
			}
			case 0:
			{
				cout << "���¼�" << endl;
				break;
			}
			}
			break;
		}
		h = h->next;
	}
	if (judge_exist == false)
	{
		cout << "-----���������Ʒid�����ڣ�-----" << endl;
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
	orders_head->time = time;//��ȡ����ʱ��
	orders_head->num=stoi(num);
	orders_head->buyer_id = buyer_id;
	orders_head->g_id = g_id;
	orders_head->seller_id= seller_id;
	modify_file(1);
	modify_file(0);
	modify_file(-1);
}
void buyer_remove_good(string id)//��������ʱ����������������
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
	cout << "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.��ϵ�����û� 7.�����û������� 8.����" << endl;
	cout << "===============================================================================================================" << endl;
	if (current_user->message!="")	cout<<"-----ע�⣡���µ���Ϣ��-----"<<endl;
	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
}
void buyer()  //��ҽ���
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
			cout << endl << "��������Ʒid:";
			string id;
			cin.sync();
			getline(cin,id);
			int num,i=0;
			bool judge_num=true;//�ж�����������Ƿ�Ϸ���
			string str;
			cout<<"������������";
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
						cout<<endl<<"-----�����������������룡-----"<<endl;
						cout<<"������������";
						break;
					}
					i++;
				}
				if (judge_num) break;
			}
			num=stoi(str);
			bool judge = 0;//�жϽ����Ƿ�ɹ�
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
						string exp1=make_update("commodity","���� = "+to_string(h->num-num),"��ƷID",h->id);
						analyse_sql(exp1,0);
						if (h->num-num==0)
						{
							string exp3=make_update("commodity","��Ʒ״̬ = ���¼�","��ƷID",h->id);
							analyse_sql(exp3,0);
						}
						string price=to_string(h->price);
						for (int i=1;i<=5;i++)	price.pop_back();
						current_user->money_exp+=("-"+to_string(num)+"*"+price);//���ɱ��ʽ
						current_user->money=stod(calculator(current_user->money_exp));//ͨ�����ʽ������
						users* seller=users_head;
						while (seller!=NULL) //��������Ʒ������Ǯ�����ӡ�
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
						cout << endl << "******************************" << endl << "�������ѣ�" << endl << "����ʱ�䣺";
						orders* newone = new orders;
						newone->id = "T000";    //��ȡ������
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
						cout << newone->time<<endl<<"���׵��ۣ�"<<h->price<<endl<<"����������"<<num<<endl<<"����״̬���ɹ�"<<endl<<"�˻���"<<current_user->money;
						cout << endl << "******************************"<<endl;
					}
					else
					{
						cout << endl << "******************************" << endl << "����ʧ�ܣ�" ;
						cout << endl << "�������㣡" << endl<<"******************************";
					}
				}
				else
				{
					cout << endl << "******************************" << endl << "����ʧ�ܣ�" ;
					cout << endl << "��Ʒ������㣡" << endl<<"******************************";
				}
			}
			else
			{
				cout << endl << "******************************" << endl << "����ʧ�ܣ�" ;
				cout << endl << "��Ʒid�����ڣ�" << endl << "******************************"<<endl;
			}
			cout << endl<<endl<<endl;
			buyer_View();
			break;
		}
		case 51:
		{
			cout << endl << "������Ҫ���������ƣ�";
			string name;
			cin.sync();
			getline(cin,name);
			string exp=make_select("commodity","����",name);
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
			cout << endl << "����������鿴����ƷID��";
			string id;
			cin.sync();
			getline(cin,id);
			string exp=make_select("commodity","��ƷID",id);
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
			cout<<endl<<"-----��Ч���룡���������룡-----"<<endl;
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
		}
		cin.sync();
		key = getchar();
	}
	cout<<endl<<endl<<"**********��������������˵���**********"<<endl;
	cin.sync();
	getchar();
	personal_menu();
}