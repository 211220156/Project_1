#include "chatting.h"
void print_chat_history(string sender_id,string receiver_id,string receiver_name)
{
	cout<<endl<<"以下为您与id为"<<receiver_id<<"，昵称为"<<receiver_name<<"的聊天记录！"<<endl;
	cout<<"======================================================================"<<endl;
	ifstream ifs("chat_history.txt",ios::in);
    bool judge=false;//判断有无聊天记录
	if (!ifs.is_open())
		cout<<"你和此用户暂无聊天记录！"<<endl;
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
					cout<<time<<endl<<"您："<<content<<endl<<endl;
				else
					cout<<time<<endl<<receiver_name<<"（对方）:"<<content<<endl<<endl;
			}
            getline(ifs,str);
		}
		if (!judge) cout<<"你和此用户暂无聊天记录！"<<endl;
	}
	ifs.close();
    
	cout<<"======================================================================"<<endl;
}

void chat_with_other()
{
    if (current_user->message!="")
	{
		cout<<endl<<"新消息："<<endl;
		for (int i=0;i<current_user->message.size();i++)
		{
			if (current_user->message[i]=='/')
				cout<<endl;
			else
				cout<<current_user->message[i];	
		}
		current_user->message="";
	}
    cout<<endl<<endl<<"所有用户如下：";
    users* h = users_head;
	cout << endl << "************************************************************" << endl;
	cout << "用户ID\t\t用户名\t\t联系方式"<<endl;
	while (h != NULL)
	{
		cout << left << h->id << "\t\t" << setw(11) << h->name << "\t" << h->contact <<endl;
		h = h->next;
	}
	cout<< "************************************************************" << endl;
	cout<<endl<<"请输入你要联系的用户ID：";
	cin.sync();
	string id;
	getline(cin,id);
	if (id==current_user->id)
		cout<<endl<<"-----不允许向自己发送信息！-----"<<endl;
	else
	{
		users* user=users_head;
		bool judge=false;//判断用户id是否存在
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
			cout<<endl<<"-----用户id不存在！-----"<<endl;
		else
		{
			print_chat_history(current_user->id,id,user->name);
			cout<<endl<<"请输入你要发送的信息，输入“退出”返回主界面：";
			cin.sync();
			string content;
			getline(cin,content);
			while (content!="退出")
			{
				if (content=="查找聊天记录")
					print_chat_history(current_user->id,id,user->name);
				else
				{
					user->message+="/"+current_user->id+" "+current_user->name+"："+content;
					modify_chat_history(get_accurate_time()+" "+current_user->id+" "+id+" "+content);
					cout<<endl<<"信息发送成功！（若想查看聊天记录，可输入“查找聊天记录”）"<<endl<<endl;
				}
				cout<<"请输入你要发送的信息，输入“退出”返回主界面：";
				cin.sync();
				getline(cin,content);
			}
            cout<<endl<<"-----您已退出聊天窗口！-----";
		}
	}
}