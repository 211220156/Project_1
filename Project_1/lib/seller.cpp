#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
#include "seller.h"
#include "chatting.h"
extern bool bool_user, bool_admin;  //�ж��û��Ƿ��ڵ�¼״̬
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //��ʼ�����˹���Ա�˻�
extern string admin_pwd ;
void seller_all_goods()
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
	cout << endl << endl << "����������Ʒ���£�"<<endl<<"****************************************************************************************************"<<endl;
	cout << "��ƷID\t\t����\t\t�۸�\t\t����\t\t�ϼ�ʱ��\t\t��Ʒ״̬" << endl;
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
	sort(a.begin(),a.end(),cmp);//�Ӵ�С������
	if (key!=50)
	{
		for (int i=a.size()-1;i>=0;i--)
		{
			cout << left << a[i]->id << "\t\t" << setw(11) << a[i]->name << "\t" << a[i]->price << "\t\t" <<a[i]->num<<"\t\t"<< a[i]->on_shelf_time << "\t\t";
			if (a[i]->status == 1) cout << "������" << endl;
			if (a[i]->status == 0) cout << "���¼�" << endl;
		}
	}
	else
	{
		for (int i=0;i<a.size();i++)
		{
			cout << left << a[i]->id << "\t\t" << setw(11) << a[i]->name << "\t" << a[i]->price << "\t\t" <<a[i]->num<<"\t\t"<< a[i]->on_shelf_time << "\t\t";
			if (a[i]->status == 1) cout << "������" << endl;
			if (a[i]->status == 0) cout << "���¼�" << endl;
		}
	}
	if (exist == false)
		cout << "����δ�����κ���Ʒ��" << endl;
	cout << "****************************************************************************************************" << endl;
}
void seller_all_orders()
{
	orders* h = orders_head;
	cout << endl << "������ʷ�۳��������£�"<<endl;
	bool exist = false;
	cout << "****************************************************************************************************" << endl;
	cout << "����ID\t\t��ƷID\t\t����\t\t����\t\t����ʱ��\t\t���ID" << endl;
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
		cout << "���������ʷ������" << endl;
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
				cout << endl << "��ȷ��Ҫ�¼ܸ���Ʒ��" << endl << endl << "******************************" << endl;
				cout << "��ƷID��" << h->id << endl;
				cout << "��Ʒ���ƣ�" << h->name << endl;
				cout << "��Ʒ�۸�" << h->price << endl;
				cout << "��Ʒ������" << h->num << endl;
				cout << "�ϼ�ʱ�䣺" << h->on_shelf_time << endl;
				cout << "��Ʒ������" << h->description << endl;
				cout << "******************************" << endl << endl << "��ѡ��y/n����";
				cin.sync();
				int option = getchar();
				if (option == 121)
				{
					if (h->status == 1)
					{
						string exp=make_update("commodity","��Ʒ״̬ = ���¼�","��ƷID",h->id);
						cout << endl << endl << "******************************" << endl;
						cout << "�¼ܸ���Ʒ�ɹ���" << endl;
						h->status = 0;
						modify_file(0);
						break;
					}
					if (h->status == 0)
					{
						cout << endl << endl << "******************************" << endl;
						cout << "�¼�ʧ�ܣ�����Ʒ��Ϊ�¼�״̬��" << endl;
						break;
					}
				}
				else
				{
					if (option == 110)
					{
						cout << endl << endl << "******************************" << endl;
						cout << "����ȡ���¼ܣ�" << endl;
						break;
					}
					else
					{
						cout << endl << endl << "******************************" << endl;
						cout << "�¼�ʧ�ܣ�������y/n��" << endl;
						break;
					}
				}
			}
			else
			{
				cout << endl << endl << "******************************" << endl;
				cout <<"�Բ��𣡴���Ʒ�������������ģ���û��Ȩ���¼ܣ�" << endl<<endl;
				break;
			}
		}
		h = h->next;
	}
	if (exist == false)
	{
		cout << endl << endl << "******************************" << endl;
		cout << "�¼�ʧ�ܣ�����ƷID�����ڣ�" << endl;
	}
}
void seller_modify_good(int kind,string content,string id)
{
	goods* h=goods_head;
	while (h!=NULL)
	{
		if (h->id==id)
		{
			if (kind==1)//�޸ļ۸�
			{
				h->price=stod(content);
				modify_file(0);
			}
			else if (kind==2)//�޸�����
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
	cout << endl << "������Ʒ�ɹ���" << endl<<"******************************";
	goods_head->id = "M000";    //��ȡ��Ʒid
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
	cout << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.��ϵ�����û� 7.�����û������� 8.����" << endl;
	cout << "==============================================================================================================" << endl;
	if (current_user->message!="")	cout<<"-----ע�⣡���µ���Ϣ��-----"<<endl;
	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
}
void seller() //���ҽ���
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
			cout << endl << endl << "��������Ʒ���ƣ�";
			cin.sync();
			getline(cin,newone->name);
			cout << "��������Ʒ�۸�";
			string temp;
			while (1) // �ж�����ļ۸��Ƿ�Ϸ�
			{
				cin.sync();
				getline(cin,temp);
				if (judge_price(temp))
					break;
				else
				{
					cout<<endl<<"-----������Ч�����������룡-----"<<endl<<endl;
					cout << "��������Ʒ�۸�";
				}
			}
			newone->price=stod(temp);
			cout<<"��������Ʒ������";
			while (1) //�ж������ĺϷ���
			{
				cin.sync();
				getline(cin,temp);
				if (judge_num(temp))
					break;
				else
				{
					cout<<endl<<"-----������Ч�����������룡-----"<<endl<<endl;
					cout << "��������Ʒ������";
				}
			}
			newone->num=stoi(temp);
			cout << "��������Ʒ������";
			cin.sync();
			getline(cin,newone->description);
			cout << endl << endl << "��ȷ���������Ʒ��Ϣ����" << endl << "******************************" << endl;
			cout << "��Ʒ���ƣ�" << newone->name << endl << "��Ʒ�۸�" << newone->price << endl <<"��Ʒ������"<<newone->num<<endl<< "��Ʒ������" << newone->description << endl;
			cout << "******************************" << endl << endl << "��ȷ��Ҫ��������Ʒ��y/n��:";
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
					cout << endl << "-----ȡ����������Ʒ��-----" << endl;
				}
				else
				{
					cout << endl << "-----������Ʒʧ�ܣ�������y��n��-----" << endl;
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
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 51:
		{
			cout << endl << "************************************************************" << endl;
			cout << "��������Ҫ�޸ĵ���ƷID��";
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
						cout<<endl<<"�Բ��𣡴���Ʒ����������������Ʒ������Ȩ�޸ģ�"<<endl;
						break;
					}
					cout << "������Ҫ�޸ĵ���Ϣ��1.�۸� 2.��Ʒ��������";
					cin.sync();
					int option = getchar();
					switch (option)
					{
					case 49:
					{
						cout << "�������޸ĺ����Ʒ�۸�";
						string price;
						while (1) // �ж�����ļ۸��Ƿ�Ϸ�
						{
							cin.sync();
							getline(cin,price);
							if (judge_price(price))
								break;
							else
							{
								cout<<endl<<"-----������Ч�����������룡-----"<<endl<<endl;
								cout << "�������޸ĺ����Ʒ�۸�";
							}
						}
						cout << endl << "��ȷ���޸ĺ����Ʒ��Ϣ��"<<endl;
						cout << endl << "****************************************" << endl;
						cout << "��ƷID:" << h->id << endl;
						cout << "��Ʒ���ƣ�" << h->name << endl;
						cout << "��Ʒ�۸�" << price <<"Ԫ" << endl;
						cout << "��Ʒ������" << h->description << endl;
						cout << "****************************************" << endl;
						cout << endl<<"ȷ���޸ģ�(y/n)��" ;
						cin.sync();
						int o = getchar();
						switch (o)
						{
						case 121:
						{
							cout << endl << "-----�޸ĳɹ���-----" <<endl<< endl << "************************************************************" << endl;
							price=to_string(stod(price));
							for (int i=1;i<=5;i++)	price.pop_back();
							string exp=make_update("commodity","�۸� = "+price,"��ƷID",h->id);
							analyse_sql(exp,-1);
						/*	h->price = stod(price);
							modify_file(0);
						*/	break;
						}
						case 110:
						{
							cout << endl << "-----ȡ���޸ģ�-----"<<endl << endl << "************************************************************" << endl;
							break;
						}
						default:
							cout << endl << "-----�޸�ʧ�ܣ�������y/n��-----" <<endl<< endl << "************************************************************" << endl;
							break;
						}
						break;
					}
					case 50:
					{
						cout  << "�������޸ĺ����Ʒ������";
						string d;
						cin.sync();
						getline(cin,d);
						cout << endl << "��ȷ���޸ĺ����Ʒ��Ϣ��" << endl;
						cout << endl << "****************************************" << endl;
						cout << "��ƷID:" << h->id << endl;
						cout << "��Ʒ���ƣ�" << h->name << endl;
						cout << "��Ʒ�۸�" << h->price << "Ԫ" << endl;
						cout << "��Ʒ������" << d << endl;
						cout << "****************************************" << endl;
						cout <<endl<< "ȷ���޸ģ�(y/n)��";
						cin.sync();
						int o = getchar();
						switch (o)
						{
						case 121:
						{
							cout << endl << "-----�޸ĳɹ���-----"<<endl << endl << "************************************************************" << endl;
							string exp=make_update("commodity","���� = "+d,"��ƷID",h->id);
							analyse_sql(exp,-1);
						/*	h->description=d;
							modify_file(0);
						*/	break;
						}
						case 110:
						{
							cout << endl << "-----ȡ���޸ģ�-----" << endl<<endl << "************************************************************" << endl;
							break;
						}
						default:
							cout << endl << "-----�޸�ʧ�ܣ�������y/n��-----" <<endl<< endl << "************************************************************" << endl;
							break;
						}
						break;

					}
					default:
						cout << endl << "-----û�ж�Ӧ����Ʒ���ԣ��޸�ʧ�ܣ�-----" <<endl<<endl<< "************************************************************" << endl;
						break;
					}
					break;
				}
				h = h->next;
			}
			if (exist == false)
			{
				cout << endl << "���������ƷID�����ڣ�" << endl;
				cout << "************************************************************" << endl;
			}
			cout << endl<<endl;
			seller_View();
			break;
		}
		case 52://�¼���Ʒ
		{
			cout << endl << "******************************" << endl;
			cout << "��������Ҫ�¼ܵ���Ʒ��ID��";
			string id;
			cin.sync();
			getline(cin,id);
			string exp=make_update("commodity","��Ʒ״̬ = ���¼�","��ƷID",id);
			analyse_sql(exp,-1);
			cout<<endl<<endl;
			seller_View();
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 53://�鿴��ʷ����
		{
			string exp=make_select("order","","");
			analyse_sql(exp,-1);
			cout<<endl<<endl;
			seller_View();
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 54:
		{
			chat_with_other();
			cout << endl<<endl<<"���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 56:
		{
			system("cls");
			seller_View();
			break;
		}
		default:
			cout<<endl<<"-----������Ч�����������룡-----"<<endl;
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		cin.sync();
		key = getchar();
	}
	personal_menu();
}