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
	int legitimacy(string &exp);//�жϺϷ��ԡ��Ϸ�����0�����������÷���1��Բ���Ų�ƥ�䷵��2�����ָ�ʽ���󷵻�3������Ϊ0����4
	string calculate(vector<string> suffix);
	friend string calculator(string &str);
	vector<string> infix_to_suffix(string &exp);
};