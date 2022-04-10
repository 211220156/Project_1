#pragma once
#include "trading_platform.h"
void analyse_sql(string exp,int identity);//1为管理员，0买家，-1卖家
string make_select(string name,string column, string value);
string make_update(string name,string content,string con1,string con2);
string make_insert(string name, string values);