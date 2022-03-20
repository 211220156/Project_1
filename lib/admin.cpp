#include "trading_platform.h"
#include "calculator.h"
#include "sql_coping.h"
#include "admin.h"
extern bool bool_user, bool_admin;  //�ж��û��Ƿ��ڵ�¼״̬
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //��ʼ�����˹���Ա�˻�
extern string admin_pwd ;
void admin_all_goods()
{
	cout << endl << endl << "*******************************************************************************************************************" << endl;
	cout << "ID\t\t����\t\t�۸�\t\t�ϼ�ʱ��\t\t����id\t\t����\t\t��Ʒ״̬" << endl;
	goods* h = goods_head;
	while (h != NULL)
	{
		cout << left;
		cout << h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" << h->on_shelf_time << "\t\t" << h->seller_id <<"\t\t"<<h->num<<"\t\t";
		if (h->status == 1) cout << "������" << endl;
		if (h->status == 0) cout << "���¼�" << endl;
		h = h->next;
	}
	cout << "*******************************************************************************************************************" << endl;
}
void admin_search_good(string name)
{
	cout << endl << endl << "*******************************************************************************************************************" << endl;
	cout << "ID\t\t����\t\t�۸�\t\t�ϼ�ʱ��\t\t����id\t\t����\t\t��Ʒ״̬" << endl;
	bool j = false;//�ж��Ƿ���ڸ���Ʒ
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
				if (h->status == 1) cout << "������" << endl;
				if (h->status == 0) cout << "���¼�" << endl;
			}
		}
		h = h->next;
	}
	if (j == false)
		cout << "-----�Բ����޷�����������Ʒ��-----" << endl;
	cout << "*******************************************************************************************************************" << endl;
}
void admin_all_orders()
{
	orders* h = orders_head;
	cout << endl << "**********************************************************************" << endl;
	cout << "����id\t��Ʒid\t����\t����\t����ʱ��\t����id\t" << endl;
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
	cout << "�û�ID\t\t�û���\t\t��ϵ��ʽ\t��ַ\t\t\t���\t\t�û�״̬"<<endl;
	while (h != NULL)
	{
		cout << left << h->id << "\t\t" << setw(11) << h->name << "\t" << h->contact << "\t" << setw(21) << h->address << "\t" << h->money<<"\t\t";
		if (h->status)	cout<<"����"<<endl;	else	cout<<"���"<<endl;
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
			cout << endl << "-----��ȷ��Ҫ�¼ܸ���Ʒ��-----"<<endl<<endl<<"******************************"<<endl;
			cout << "��ƷID��" << h->id << endl;
			cout << "��Ʒ���ƣ�" << h->name << endl;
			cout << "��Ʒ�۸�" << h->price << endl;
			cout<<"��Ʒ������"<<h->num<<endl;
			cout<<"�ϼ�ʱ�䣺"<<h->on_shelf_time<<endl;
			cout << "��Ʒ������" << h->description << endl;
			cout << "******************************" << endl << endl << "��ѡ��y/n����";
			cin.sync();
			int option = getchar();
			if (option == 121)
			{
				if (h->status == 1)
				{
					cout << endl << endl << "******************************" << endl;
					cout << "-----�¼ܸ���Ʒ�ɹ���-----" << endl;
					h->status = -1;
					modify_file(0);
					break;
				}
				if (h->status == 0)
				{
					cout << endl << endl << "******************************" << endl;
					cout << "-----�¼�ʧ�ܣ�����Ʒ��Ϊ�¼�״̬��-----" << endl;
					break;
				}
			}
			else
			{
				if (option == 110)
				{
					cout << endl << endl << "******************************" << endl;
					cout << "-----����ȡ���¼ܣ�-----" << endl;
					break;
				}
				else
				{
					cout << endl << endl << "******************************" << endl;
					cout << "-----�¼�ʧ�ܣ�������y/n��-----" << endl;
					break;
				}
			}
		}
		h = h->next;
	}
	if (exist == false)
	{
		cout<< endl << endl << "******************************" << endl;
		cout << "-----�¼�ʧ�ܣ�����ƷID�����ڣ�-----" << endl;
	}
}
void admin_ban_user(string id)
{
	users* curr = users_head;
	bool exist = false; //�жϴ�id�Ƿ����
	bool judge=false;//�жϷ���Ƿ�ɹ�
	while (curr != NULL)
	{
		if (curr->id == id)
		{
			exist = true;
			cout << endl << "-----��ȷ��Ҫ������û���-----" << endl << endl << "*************************" << endl;
			cout << "�û�ID��" << curr->id << endl;
			cout << "�û�����" << curr->name << endl;
			cout << "��ϵ��ʽ��" << curr->contact << endl;
			cout<<"�û���ַ��"<<curr->address<<endl;
			cout<<"Ǯ����"<<curr->money<<endl;
			cout << "*************************" << endl << endl << "��ѡ��y/n����";
			cin.sync();
			int option = getchar();
			if (option == 121)
			{
				cout << endl << endl << "***********************************" << endl;
				cout << "-----����û��ɹ���-----" << endl;
				curr->status=false;
				judge=true;
				modify_file(1);
			}
			else
			{
				if (option == 110)
				{
					cout << endl << endl << "***********************************" << endl;
					cout << "-----����ȡ�������-----" << endl;
				}
				else
				{
					cout << endl << endl << "***********************************" << endl;
					cout << "-----���ʧ�ܣ�������y/n��-----" << endl;
				}
			}
			break;
		}
		curr = curr->next;
	}
	if (exist==false)
	{
		cout << endl << endl << "***********************************" << endl<<endl;
		cout << "-----����û�ʧ�ܣ��û�ID�����ڣ�-----" << endl;
	}
	if (judge)
	{
		goods* h=goods_head;
		while (h!=NULL)
		{
			if (h->seller_id==curr->id)
			{
				string exp=make_update("commodity","��Ʒ״̬ = ���¼�","����ID",h->seller_id);
				h->status=false;
				modify_file(0);
			}
			h=h->next;
		}
	}
}

void admin_menu() //����Ա����
{
	system("cls");
	cout << "================================================================================" << endl;
	cout << "1.�鿴������Ʒ 2.������Ʒ 3.�鿴���ж��� 4.�鿴�����û� 5.����û� 6.�¼���Ʒ 7.ע��" << endl;
	cout << "================================================================================" << endl;
	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
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
			cout << "ID\t\t����\t\t�۸�\t\t�ϼ�ʱ��\t\t����id\t\t����\t\t��Ʒ״̬" << endl;
			goods* h = goods_head;
			while (h != NULL)
			{
				cout << left;
				cout << h->id << "\t\t" << setw(11)<<h->name << "\t" << h->price << "\t\t" << h->on_shelf_time << "\t\t" << h->seller_id <<"\t\t"<<h->num<<"\t\t";
				if (h->status == 1) cout << "������" << endl;
				if (h->status == 0) cout << "���¼�" << endl;
				h = h->next;
			}
			cout << "*******************************************************************************************************************" << endl;
		*/	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 50:
		{
			cout << endl << "������Ҫ���������ƣ�";
			string name;
			cin.sync();
			getline(cin,name);
			string exp=make_select("commodity","����",name);
			analyse_sql(exp,1);
		/*	cout << endl << endl << "*******************************************************************************************************************" << endl;
			cout << "ID\t\t����\t\t�۸�\t\t�ϼ�ʱ��\t\t����id\t\t����\t\t��Ʒ״̬" << endl;
			bool j = false;//�ж��Ƿ���ڸ���Ʒ
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
						if (h->status == 1) cout << "������" << endl;
						if (h->status == 0) cout << "���¼�" << endl;
					}
				}
				h = h->next;
			}
			if (j == false)
				cout << "-----�Բ����޷�����������Ʒ��-----" << endl;
			cout << "*******************************************************************************************************************" << endl;
		*/	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 51:
		{
			string exp=make_select("order","","");
			analyse_sql(exp,1);
		/*	orders* h = orders_head;
			cout << endl << "**********************************************************************" << endl;
			cout << "����id\t��Ʒid\t����\t����\t����ʱ��\t����id\t" << endl;
			while (h != NULL)
			{
				cout << h->id << "\t" << h->g_id << "\t" << h->amount << "\t" <<h->num<<"\t"<< h->time << "\t" << h->seller_id << endl;
				h = h->next;
			}
			cout << "**********************************************************************" << endl;
		*/	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 52:
		{
			string exp=make_select("user","","");
			analyse_sql(exp,1);
		/*	users* h = users_head;
			cout << endl << "*******************************************************************************************************************" << endl;
			cout << "�û�ID\t\t�û���\t\t��ϵ��ʽ\t��ַ\t\t\t���\t\t�û�״̬"<<endl;
			while (h != NULL)
			{
				cout << left << h->id << "\t\t" << setw(11) << h->name << "\t" << h->contact << "\t" << setw(21) << h->address << "\t" << h->money<<"\t\t";
				if (h->status)	cout<<"����"<<endl;	else	cout<<"���"<<endl;
				h = h->next;
			}
			cout<< "*******************************************************************************************************************" << endl;
		*/	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 53:
		{
			cout << endl << "��������Ҫ������û�ID��";
			string id;
			cin.sync();
			getline(cin,id);
			string exp1=make_update("user","�û�״̬ = ���","�û�ID",id);
			analyse_sql(exp1,1);
		/*	users* prev = NULL;
			users* curr = users_head;
			bool exist = false; //�жϴ�id�Ƿ����
			bool judge=false;//�жϷ���Ƿ�ɹ�
			while (curr != NULL)
			{
				if (curr->id == id)
				{
					exist = true;
					cout << endl << "-----��ȷ��Ҫ������û���-----" << endl << endl << "*************************" << endl;
					cout << "�û�ID��" << curr->id << endl;
					cout << "�û�����" << curr->name << endl;
					cout << "��ϵ��ʽ��" << curr->contact << endl;
					cout<<"�û���ַ��"<<curr->address<<endl;
					cout<<"Ǯ����"<<curr->money<<endl;
					cout << "*************************" << endl << endl << "��ѡ��y/n����";
					cin.sync();
					int option = getchar();
					if (option == 121)
					{
						if (prev == NULL)
						{
							users_head = curr->next;
							delete curr;
							cout << endl << endl << "***********************************" << endl;
							cout << "-----����û��ɹ���-----" << endl;
							judge=true;
							modify_file(1);
						}
						else
						{
							prev->next = curr->next;
							delete curr;
							cout << endl << endl << "***********************************" << endl;
							cout << "-----����û��ɹ���-----" << endl;
							judge=true;
							modify_file(1);
						}
					}
					else
					{
						if (option == 110)
						{
							cout << endl << endl << "***********************************" << endl;
							cout << "-----����ȡ�������-----" << endl;
						}
						else
						{
							cout << endl << endl << "***********************************" << endl;
							cout << "-----���ʧ�ܣ�������y/n��-----" << endl;
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
				cout << "-----����û�ʧ�ܣ��û�ID�����ڣ�-----" << endl;
			}
			if (judge)
			{
				goods* h=goods_head;
				while (h!=NULL)
				{
					if (h->seller_id==curr->id)
					{
						string exp2=make_update("commodity","��Ʒ״̬ = ���¼�","����ID",h->seller_id);
						h->status=false;
						modify_file(0);
						break;
					}
				}
			}
		*/	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 54:
		{
			cout << endl << "******************************" << endl;
			cout << "��������Ҫ�¼ܵ���Ʒ��ID��";
			string id;
			cin.sync();
			getline(cin,id);
			string exp=make_update("commodity","��Ʒ״̬ = ���¼�","��ƷID",id);
			analyse_sql(exp,1);
		/*	goods* h = goods_head;
			bool exist = false;
			while (h != NULL)
			{
				if (h->id == id)
				{
					exist = true;
					cout << endl << "-----��ȷ��Ҫ�¼ܸ���Ʒ��-----"<<endl<<endl<<"******************************"<<endl;
					cout << "��ƷID��" << h->id << endl;
					cout << "��Ʒ���ƣ�" << h->name << endl;
					cout << "��Ʒ�۸�" << h->price << endl;
					cout<<"��Ʒ������"<<h->num<<endl;
					cout<<"�ϼ�ʱ�䣺"<<h->on_shelf_time<<endl;
					cout << "��Ʒ������" << h->description << endl;
					cout << "******************************" << endl << endl << "��ѡ��y/n����";
					cin.sync();
					int option = getchar();
					if (option == 121)
					{
						if (h->status == 1)
						{
							cout << endl << endl << "******************************" << endl;
							cout << "-----�¼ܸ���Ʒ�ɹ���-----" << endl;
							h->status = -1;
							modify_file(0);
							break;
						}
						if (h->status == 0)
						{
							cout << endl << endl << "******************************" << endl;
							cout << "-----�¼�ʧ�ܣ�����Ʒ��Ϊ�¼�״̬��-----" << endl;
							break;
						}
					}
					else
					{
						if (option == 110)
						{
							cout << endl << endl << "******************************" << endl;
							cout << "-----����ȡ���¼ܣ�-----" << endl;
							break;
						}
						else
						{
							cout << endl << endl << "******************************" << endl;
							cout << "-----�¼�ʧ�ܣ�������y/n��-----" << endl;
							break;
						}
					}
				}
				h = h->next;
			}
			if (exist == false)
			{
				cout<< endl << endl << "******************************" << endl;
				cout << "-----�¼�ʧ�ܣ�����ƷID�����ڣ�-----" << endl;
			}
		*/	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		default:
			cout<<endl<<"-----��Ч���룡���������룡-----"<<endl;
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
		}
		cin.sync();
		key = getchar();
	}
	bool_admin = false;
	cout << endl << "***************ע���ɹ�������������������档***************" << endl;
	cin.sync();
	getchar();
	Init_View();
}