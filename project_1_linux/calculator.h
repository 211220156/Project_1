#include <string>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
extern bool JUDGE_ANS;
string calculator(string &str);
class counter
{
	string exp;
public:
	counter(string str){exp=str;}
	bool judge_number(char c);
	bool judge_operator(char c);
	void remove_space(string &exp);
	int get_priority(char c);
	int legitimacy(string &exp);//判断合法性。合法返回0，操作符误用返回1，圆括号不匹配返回2，数字格式有误返回3，除数为0返回4
	string calculate(vector<string> suffix);
	friend string calculator(string &str);
	vector<string> infix_to_suffix(string &exp);
};