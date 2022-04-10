#include "trading_platform.h"
#include "admin.h"
#include "seller.h"
#include "buyer.h"
string make_select(string name,string column, string value)
//identity:管理员是1，卖家是0，买家-1 kind:select为1，update为0，insert为-1  
{
    string ans="SELECT * FROM ";
    ans+=name;
    if (column!="" && value!="")
        ans+=" WHERE "+column+" CONTAINS "+value;
    modify_sql(get_accurate_time()+" "+ans);
    return ans;
}
string make_update(string name,string content,string con1,string con2)
{
    string ans="UPDATE "+name+" SET "+content+" WHERE "+con1+" = "+con2;
    modify_sql(get_accurate_time()+" "+ans);
    return ans;
}
string make_insert(string name, string values)
{
    string ans="INSERT INTO "+name+" VALUES "+values;
    modify_sql(get_accurate_time()+" "+ans);
    return ans;
}

void analyse_sql(string exp,int identity)
{
    switch (exp[0])
    {
        case 'S':
        {
            if (exp.size()>23)//说明后面包含WHERE
            {
                string name;
                for (int i=1;i<exp.size();i++)
                {
                    if (exp[i]=='S')
                    {
                        name=exp.substr(i+2);
                        break;
                    }
                }
                if (name[0]!='M')
                {
                    if (identity==1)    admin_search_good(name);
                    if (identity==0)    buyer_search_good(name);
                }
                else
                    buyer_good_details(name);
            }
            else
            {
                if (exp[14]=='c')
                {
                    if (identity==1)    admin_all_goods();
                    if (identity==0)    buyer_all_goods();
                    if (identity==-1)   seller_all_goods();
                }
                if (exp[14]=='o')
                {
                    if (identity==1)    admin_all_orders();
                    if (identity==0)    buyer_all_orders();
                    if (identity==-1)   seller_all_orders();
                }
                if (exp[14]=='u')
                {
                    if (identity==1)    admin_all_users();
                }
            }
            break;
        }
        case 'U':
        {
            string condition,id;
            int i=0,j=0;
            for (i=6;i<exp.size();i++)
            {
                if (exp[i]=='T')
                {
                    for (j=i+2;j<exp.size();j++)
                    {
                        if (exp[j+1]=='W')
                            break;
                        else
                            condition+=exp[j];
                    }
                    for (;j<exp.size();j++)
                    {
                        if (exp[j]=='=')
                        {
                            id=exp.substr(j+2);
                            break;
                        }
                    }
                    break;
                }
            }
            if (condition=="商品状态 = 已下架")
            {
                if (id[0]!='U')
                {
                    if (identity==1)    admin_remove_good(id);
                    if (identity==-1)   seller_remove_good(id);
                    if (identity==0)    buyer_remove_good(id);    
                }
                else
                {
                    goods* h=goods_head;
                    while (h!=NULL)
                    {
                        if (h->seller_id==id)
                        {
                            if (identity==1)    admin_remove_good(h->id);
                            if (identity==-1)   seller_remove_good(h->id);
                        }
                        h=h->next;
                    }
                }
            }
            else if (condition=="用户状态 = 封禁")
            {
                admin_ban_user(id);
            }
            else
            {
                if (search("价格",condition.c_str())==0)//若是对价格进行修改
                {
                    string price;
                    for (i=0;i<condition.size();i++)
                    {
                        if (condition[i]=='=')
                        {
                            price=condition.substr(i+2);
                            break;
                        }
                    }
                    seller_modify_good(1,price,id);
                }
                if (search("描述",condition.c_str())==0)//修改描述
                {
                    string description;
                    for (i=0;i<condition.size();i++)
                    {
                        if (condition[i]=='=')
                        {
                            description=condition.substr(i+2);
                            break;
                        }
                    }
                    seller_modify_good(2,description,id);
                }
                if (search("数量",condition.c_str())==0)
                {
                    string num;
                    for (i=0;i<condition.size();i++)
                    {
                        if (condition[i]=='=')
                        {
                            num=condition.substr(i+2);
                            break;
                        }
                    }
                    seller_modify_good(3,num,id);
                }
            }
            break;
        }
        case 'I':
        {
            string content;
            for (int i=12;i<exp.size();i++)
            {
                if (exp[i]=='S')
                {
                    content=exp.substr(i+2);
                    break;
                }
            }
            if (exp[12]=='c') 
                seller_publish_good(content);
            else
                buyer_purchase_good(content);
            break;
        }
    }
}