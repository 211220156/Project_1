#include "trading_platform.h"
#include "calculator.h"
extern bool bool_user, bool_admin;  //�ж��û��Ƿ��ڵ�¼״̬
extern users* users_head ;
extern goods* goods_head ;
extern orders* orders_head ;
extern users* current_user ;
extern string admin_account ; //��ʼ�����˹���Ա�˻�
extern string admin_pwd ;
void Init_file(users* &users_head,goods* &goods_head,orders* &orders_head) //��ʼ�������ĵ�
{
    string str,temp;
    int num=1;
    int i=0;
	//¼���û���Ϣ
	ifstream in_file("user.txt",ios::in);
	if (!in_file.is_open())
	{
		ofstream ofs("user.txt",ios::out);
        ofs<<"�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬";
        ofs.close();
	}
    else
    {
        getline(in_file,str);
        while (!in_file.eof())
        {
            getline(in_file,str);
            users* u=new users;
            temp="";
            i=0;
            while (str[i]!=',')
                temp+=str[i++];
            u->id=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            u->name=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            u->pwd=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            u->contact=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            u->address=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            u->money=stod(temp);
            u->money_exp+="+"+temp;
            temp=str.substr(i+1);
            if (temp=="���")
                u->status=false;
            u->number=num++;
            u->next=users_head;
            users_head=u;
            
        }
        in_file.close();
    }
	//¼�붩����Ϣ
	in_file.open("order.txt",ios::in);
	if (!in_file.is_open())
	{
		ofstream ofs("order.txt",ios::out);
        ofs<<"����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID";
        ofs.close();
	}
    else
    {
        getline(in_file,str);
        num=1;
        while (!in_file.eof())
        {
            getline(in_file,str);
            orders* o=new orders;
            temp="";
            i=0;
            while (str[i]!=',')
                temp+=str[i++];
            o->id=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            o->g_id=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            o->amount=stod(temp);
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            o->num=stoi(temp);
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            o->time=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            o->seller_id=temp;
            o->buyer_id=str.substr(i+1);
            o->number=num++;
            o->next=orders_head;
            orders_head=o;
            
        }
        in_file.close();
    }
	//¼����Ʒ��Ϣ
	in_file.open("commodity.txt",ios::in);
	if (!in_file.is_open())
	{
		ofstream ofs("commodity.txt",ios::out);
        ofs<<"��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬";
        ofs.close();
	}
    else
    {
        getline(in_file,str);
        num=1;
        while (!in_file.eof())
        {
            getline(in_file,str);
            goods* g=new goods;
            temp="";
            i=0;
            while (str[i]!=',')
                temp+=str[i++];
            g->id=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            g->name=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            g->price=stod(temp);
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            g->num=stoi(temp);
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            g->description=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            g->seller_id=temp;
            temp="";
            i++;
            while (str[i]!=',')
                temp+=str[i++];
            g->on_shelf_time=temp;
            i++;
            if (str.substr(i)=="���¼�")
                g->status=0;
            g->number=num++;
            g->next=goods_head;
            goods_head=g;
            
        }
        in_file.close();
    }
}

void modify_file(int kind) //1��ʾ�޸��û���Ϣ��0��ʾ�޸���Ʒ��-1��ʾ�޸Ķ���
{
	
	switch (kind)
	{
	case 1://�޸��û���Ϣ
	{
		ofstream ofs("user.txt",ios::out);
        ofs<<"�û�ID,�û���,����,��ϵ��ʽ,��ַ,Ǯ�����,�û�״̬";
		reverse(1);
		users* h = users_head;
		while (h != NULL)
		{
            ofs<<endl;
			ofs<<h->id<<","<<h->name<<","<<h->pwd<<","<<h->contact<<","<<h->address<<",";
            if (int(h->money*10)%10==0)
                ofs<<h->money<<".0,";
            else
                ofs<<h->money<<",";
            if (h->status)
                ofs<<"����";
            else
                ofs<<"���";
            //if (h->next!=NULL) ofs<<endl;
			h = h->next;
		}
		ofs.close();
		reverse(1);
		break;
	}
	case 0:
	{
		ofstream ofs("commodity.txt", ios::out);
        ofs<<"��ƷID,����,�۸�,����,����,����ID,�ϼ�ʱ��,��Ʒ״̬";
		reverse(0);
		goods* h = goods_head;
		while (h != NULL)
		{
            ofs<<endl;
			string status;
			if (h->status == 1)
				status = "������";
			if (h->status == 0)
				status = "���¼�";
			ofs<<h->id<<","<<h->name<<",";
            if (int(h->price*10)%10==0)
                ofs<<h->price<<".0,";
            else
                ofs<<h->price<<",";
            ofs<<h->num<<","<<h->description<<","<<h->seller_id<<","<<h->on_shelf_time<<","<<status;
            //if (h->next!=NULL) ofs<<endl;
			h = h->next;
		}
		ofs.close();
		reverse(0);
		break;
	}
	case -1:
	{
		ofstream ofs("order.txt", ios::out);
        ofs<<"����ID,��ƷID,���׵���,����,����ʱ��,����ID,���ID";
		reverse(-1);
		orders* h = orders_head;
		while (h != NULL)
		{
            ofs<<endl;
			ofs<<h->id<<","<<h->g_id<<",";
            if (int(h->amount*10)%10==0)
                ofs<<h->amount<<".0,";
            else
                ofs<<h->amount<<",";
            ofs<<h->num<<","<<h->time<<","<<h->seller_id<<","<<h->buyer_id;
            //if (h->next!=NULL) ofs<<endl;
			h = h->next;
		}
        ofs.close();
		reverse(-1);
		break;
	}
	}
}

void modify_sql(string ans)
{
    ofstream ofs("commands.txt", ios::app);
    ofs<<ans<<endl;
    ofs.close();
}

void modify_chat_history(string content)
{
    ofstream ofs("chat_history.txt", ios::app);
    ofs<<content<<endl;
    ofs.close();
}