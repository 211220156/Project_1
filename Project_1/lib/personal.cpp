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
void personal_menu() //���˽���
{
	system("cls");
	cout << "================================================================================" << endl;
	cout << "1.ע����¼ 2.������� 3.�������� 4.������Ϣ����" << endl;
	cout << "================================================================================" << endl;
	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
	cin.sync();
	int key = getchar();
	switch (key)
	{
	case 49:
	{
		cout << endl << "******ע����¼�ɹ���******"<<endl<<endl<<"-----��������������˵�-----"<<endl;
		cin.sync();
		getchar();
		bool_user = false;
		current_user = NULL;
		Init_View();
		break;
	}
	case 50:
	{
		buyer();
		break;
	}
	case 51:
	{
		seller();
		break;
	}
	case 52:
	{
		personal_info();
		break;
	}
	default:
		cout << endl << "�������Ӧ�Ĳ�������" << endl;
		cin.sync();
		getchar();
		personal_menu();
		break;
	}
}

void personal_info()  //������Ϣ����
{
	system("cls");
	cout << "================================================================================" << endl;
	cout << "1.�����û������� 2.�޸���Ϣ 3.�鿴��Ϣ 4.��ֵ" << endl;
	cout << "================================================================================" << endl;
	cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
	cin.sync();
	int key = getchar();
	string amount;
	while (key != 49)
	{
		switch (key)
		{
		case 50:
		{
			cout << endl << "��ѡ���޸ĵ����ԣ�1.�û��� 2.��ϵ��ʽ 3.��ַ 4.���룩��";
			cin.sync();
			int option = getchar();
			switch (option)
			{
			case 49:
			{
				cout << endl << "�������޸ĺ���û�����";
				string name;
				cin.sync();
				getline(cin,name);
				users* h=users_head;
				bool judge_repeat=false;
				while (h!=NULL)
				{
					if (h->name==name)
					{
						judge_repeat=true;
						break;
					}
					h=h->next;
				}
				if (judge_repeat)
				{
					cout << endl << "****************************************" << endl << "�޸�ʧ�ܣ��û����ѱ�ʹ�ã�" << endl;
				}
				else
				{
					cout << endl << "****************************************" << endl << "�޸ĳɹ���" << endl;
					current_user->name=name;
					modify_file(1);
				}
				break;
			}
			case 50:
			{
				cout << endl << "�������޸ĺ����ϵ��ʽ��";
				string contact;
				cin.sync();
				getline(cin,contact);
				cout << endl << "****************************************" << endl << "�޸ĳɹ���" << endl;
				current_user->contact = contact;
				modify_file(1);
				break;
			}
			case 51:
			{
				cout << endl << "�������޸ĺ�ĵ�ַ��";
				string address;
				cin.sync();
				getline(cin,address);
				cout << endl << "****************************************" << endl << "�޸ĳɹ���" << endl;
				current_user->address = address;
				modify_file(1);
				break;
			}
			case 52:
			{
				cout << endl << "�������޸ĺ�����룺";
				string pwd;
				cin.sync();
				getline(cin,pwd);
				cout << endl << "****************************************" << endl << "�޸ĳɹ���" << endl;
				current_user->pwd = pwd;
				modify_file(1);
				break;
			}
			default:
				cout<<endl<<"-----������Ч�����������룡-----"<<endl<<endl;
				break;
			}
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 51:
		{
			cout <<endl<< "********************"<<endl;
			cout << "�û�����" << current_user->name << endl;
			cout << "��ϵ��ʽ��" << current_user->contact << endl;
			cout << "��ַ��" << current_user->address << endl;
	//		cout << "��" << current_user->money << endl;
			cout<<"��";
			current_user->money=stod(calculator(current_user->money_exp));
			cout<<current_user->money<<endl;
			cout << "********************" << endl;
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		case 52:
		{
			cout << endl << "�������ֵ��";
			cin.sync();
			while (1)
			{
				getline(cin,amount);
				if (amount!="")
					break;
			}
			int i=0;
			bool judge_double=false;//�ж�������Ƿ���С��
			bool judge=true;//�ж������Ƿ�Ϸ�
			while (i<amount.size())
			{
				if (amount[i]=='.')
				{
					judge_double=true;
					if ((amount[i+1]>='0' && amount[i+1]<='9') && i+2==amount.size())
					{
						cout << endl << "****************************************" << endl << "��ֵ�ɹ���" << endl;
						cout << "��ǰ��";
						//current_user->money += amount;
						current_user->money_exp+=("+"+amount);//���ɱ��ʽ
						current_user->money=stod(calculator(current_user->money_exp));//ͨ�����ʽ�������
						cout<<current_user->money<<endl;
						modify_file(1);
						cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
						break;
					}
					else
					{
						judge=false;
						cout << endl << "****************************************" << endl << "��ֵʧ�ܣ�" << endl;
						cout<<"�������˴����ʽ�Ľ�"<<endl<<endl;
						cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
						break;
					}
				}
				else if (amount[i]<'0' || amount[i]>'9')
				{
					judge=false;
					cout << endl << "****************************************" << endl << "��ֵʧ�ܣ�" << endl;
					cout<<"�������˴����ʽ�Ľ�"<<endl<<endl;
					cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
					break;
				}
				i++;
			}
			if (judge && judge_double==false)
			{
				cout << endl << "****************************************" << endl << "��ֵ�ɹ���" << endl;
				cout << "��ǰ��";
				//current_user->money += amount;
				current_user->money_exp+=("+"+amount);//���ɱ��ʽ
				current_user->money=stod(calculator(current_user->money_exp));//ͨ�����ʽ�������
				cout<<current_user->money<<endl;
				modify_file(1);
				cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			}
			break;
		}
		default:
			cout<<endl<<"������Ч�����������룡"<<endl<<endl;
			cout << "���������(��һ���ַ���Ч��������Ϊ��Ч����)��";
			break;
		}
		cin.sync();
		key = getchar();
	}
	personal_menu();
}
