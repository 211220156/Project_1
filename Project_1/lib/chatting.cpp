#include "chatting.h"
void print_chat_history(string sender_id,string receiver_id,string receiver_name)
{
	cout<<endl<<"����Ϊ����idΪ"<<receiver_id<<"���ǳ�Ϊ"<<receiver_name<<"�������¼��"<<endl;
	cout<<"======================================================================"<<endl;
	ifstream ifs("chat_history.txt",ios::in);
    bool judge=false;//�ж����������¼
	if (!ifs.is_open())
		cout<<"��ʹ��û����������¼��"<<endl;
	else
	{
		string str,content,id1,id2,time;
		getline(ifs,str);
        while (!ifs.eof())
        {
			time="";
			id1="";
			id2="";
			for (int i=0;i<=18;i++)	time+=str[i];
			for (int i=20;i<=23;i++)	id1+=str[i];
			for (int i=25;i<=28;i++)	id2+=str[i];
			content=str.substr(30);
			if ((sender_id==id1 && receiver_id==id2) || (sender_id==id2 && receiver_id==id1))
			{
                judge=true;
				if (sender_id==id1)
					cout<<time<<endl<<"����"<<content<<endl<<endl;
				else
					cout<<time<<endl<<receiver_name<<"���Է���:"<<content<<endl<<endl;
			}
            getline(ifs,str);
		}
		if (!judge) cout<<"��ʹ��û����������¼��"<<endl;
	}
	ifs.close();
    
	cout<<"======================================================================"<<endl;
}

void chat_with_other()
{
    if (current_user->message!="")
	{
		cout<<endl<<"����Ϣ��"<<endl;
		for (int i=0;i<current_user->message.size();i++)
		{
			if (current_user->message[i]=='/')
				cout<<endl;
			else
				cout<<current_user->message[i];	
		}
		current_user->message="";
	}
    cout<<endl<<endl<<"�����û����£�";
    users* h = users_head;
	cout << endl << "************************************************************" << endl;
	cout << "�û�ID\t\t�û���\t\t��ϵ��ʽ"<<endl;
	while (h != NULL)
	{
		cout << left << h->id << "\t\t" << setw(11) << h->name << "\t" << h->contact <<endl;
		h = h->next;
	}
	cout<< "************************************************************" << endl;
	cout<<endl<<"��������Ҫ��ϵ���û�ID��";
	cin.sync();
	string id;
	getline(cin,id);
	if (id==current_user->id)
		cout<<endl<<"-----���������Լ�������Ϣ��-----"<<endl;
	else
	{
		users* user=users_head;
		bool judge=false;//�ж��û�id�Ƿ����
		while (user!=NULL)
		{
			if (user->id==id)
			{
				judge=true;
				break;
			}
			user=user->next;
	    }
		if (!judge)
			cout<<endl<<"-----�û�id�����ڣ�-----"<<endl;
		else
		{
			print_chat_history(current_user->id,id,user->name);
			cout<<endl<<"��������Ҫ���͵���Ϣ�����롰�˳������������棺";
			cin.sync();
			string content;
			getline(cin,content);
			while (content!="�˳�")
			{
				if (content=="���������¼")
					print_chat_history(current_user->id,id,user->name);
				else
				{
					user->message+="/"+current_user->id+" "+current_user->name+"��"+content;
					modify_chat_history(get_accurate_time()+" "+current_user->id+" "+id+" "+content);
					cout<<endl<<"��Ϣ���ͳɹ���������鿴�����¼�������롰���������¼����"<<endl<<endl;
				}
				cout<<"��������Ҫ���͵���Ϣ�����롰�˳������������棺";
				cin.sync();
				getline(cin,content);
			}
            cout<<endl<<"-----�����˳����촰�ڣ�-----";
		}
	}
}