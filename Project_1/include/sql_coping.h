#pragma once
#include "trading_platform.h"
void analyse_sql(string exp,int identity);//1Ϊ����Ա��0��ң�-1����
string make_select(string name,string column, string value);
string make_update(string name,string content,string con1,string con2);
string make_insert(string name, string values);