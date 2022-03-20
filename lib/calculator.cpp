#include "calculator.h"
extern bool JUDGE_ANS;
bool JUDGE_ANS=false;
void counter::remove_space(string &exp)  //�Ƴ������������֮��Ŀո񣬷�������
{
    int i=0;
    string ans;
    while (i<exp.size())
    {
        if (exp[i]!=' ')
            ans+=exp[i];
        i++;
    }
    exp=ans;
}
int counter::legitimacy(string &exp)
{
    int i=0;
    while (i<exp.size())
    {
        if (judge_number(exp[i]))
        {
            if (exp[i+1]==' ')
            {
                i++;
                while (i<exp.size() && exp[i]==' ')    i++;
                if (i!=exp.size() && judge_number(exp[i]))  return 3;//����Ҫ�ر��ж�һ�£�����֮���пո�Ҳ�ǷǷ���
            }
        }
        i++;
    }
    remove_space(exp);//�Ƴ����пո񣬷������㡣
    //���ж����޲������������
    i=0;
    while (i<exp.size())
    {
        if (judge_operator(exp[i]))
        {
            if ((!judge_number(exp[i-1])) && exp[i]!='-' && exp[i-1]!=')')   return 1;
            //�������ǰһλ�������� �� ���������Ϊ���� �� ǰһλ��Ϊ�����ţ����в���������
            if (!judge_number(exp[i+1]) && exp[i+1]!='(')    return 1;
            //���������һλ�������� �� ���������ţ����в���������
        }
        //cout<<i-1<<endl<<exp[i-1]<<endl;
        if (exp[i]=='(' && i!=0 && judge_number(exp[i-1]))
            return 1; //�ж����� 2(2*3) �������س˺ŵĴ���
        if (exp[i]=='('&& exp[i+1]==')')//����������Ҳ�����
            return 1;
        i++;
    }
    i=0;
    //�ж�����Բ���Ų�ƥ������
    int left=0,right=0;
    while (i<exp.size())
    {
        if (exp[i]=='(')
            left++;
        if (exp[i]==')')
            right++;
        i++;
    }
    if (left!=right)
        return 2;
    //�ж����ָ�ʽ�Ƿ�����
    i=0;
    while (i<exp.size())
    {
        if (exp[i]=='.')
        {
            if (!judge_number(exp[i+1]))
                return 3;//��С������治�����֣��򱨴�
            if (judge_number(exp[i+1]) && judge_number(exp[i+2]))
                return 3;//������λС��Ҳ����
        }
        if (!judge_number(exp[i]) && !judge_operator(exp[i]) && exp[i]!='(' && exp[i]!=')')
            return 3;
        i++;
    }
    return 0;
}
bool counter::judge_number(char c)
{
    if ((c>='0' && c<='9') || c=='.')
        return true;
    return false;
}
bool counter::judge_operator(char c)
{
    if (c=='+'||c=='-'||c=='*'||c=='/')
        return true;
    return false;
}

int counter::get_priority(char c)
{
    switch (c)
    {
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
    }
    return -1;
}
vector<string> counter::infix_to_suffix(string &exp)
{
    stack<char> s;
    vector<string> ans;
    string temp,str;
    int i=0;
    while (i<exp.size())
    {
        if (judge_number(exp[i]))
            temp.push_back(exp[i]);
        else
        {
            if (temp.size()>0)
                ans.push_back(temp);
            temp="";
            if (exp[i]=='-' && !(judge_number(exp[i-1])))//���и��������Ȳ���һ��0
                ans.push_back("0");
            if (exp[i]=='(')    s.push(exp[i]);
            else if (judge_operator(exp[i]))
            {
                while (1)
                {
                    if (s.empty()||s.top()=='(')
                    {
                        s.push(exp[i]);
                        break;
                    }
                    else if (get_priority(exp[i])>get_priority(s.top()))
                    {
                        s.push(exp[i]);
                        break;
                    }
                    else
                    {
                        str=s.top();
                        ans.push_back(str);
                        s.pop();
                    }
                }
            }
            else if (exp[i]==')')
            {
                while (s.top()!='(')
                {
                    str=s.top();
                    ans.push_back(str);
                    s.pop();
                }
                s.pop();
            }
        }
        i++;
    }
    if (temp.size()>0)
        ans.push_back(temp);
    while (!s.empty())
    {
        str=s.top();
        ans.push_back(str);
        s.pop();
    }
    return ans;
}

string counter::calculate(vector<string> suffix)
{
    stack<double> s;
    string ans_str;
    double op1=0,op2=0,ans=0;
    for (string i: suffix)
    {
        if (i=="+" || i=="-" || i=="/" || i=="*")
        {
            op1=s.top();
            s.pop();
            op2=s.top();
            s.pop();
            if (i=="+") ans=op1+op2;
            if (i=="-") ans=op2-op1;
            if (i=="*") ans=op1*op2;
            if (i=="/") 
            {
                if (op1==0)
                    return "���󣺳���Ϊ�㣡";//�ڴ˴��жϳ����Ƿ�Ϊ0
                ans=op2/op1;
            }
            s.push(ans);
        }
        else
            s.push(stod(i));
    }
    ans_str=to_string(s.top());//��Ϊto_stringĬ�ϱ���6λС��������Ҫpop_back 5��
    for (int i=1;i<=5;i++)
        ans_str.pop_back();
    return ans_str;
}

string calculator(string &exp)
{
    counter sub(exp);
    string ans;
    switch (sub.legitimacy(exp))
    {
        case 0:
        {
            ans=sub.calculate(sub.infix_to_suffix(exp));//��Ϊ�жϳ���Ϊ0��calculate�
                                                        //�����Ҫһ��ȫ�ֱ����ж��Ƿ���ȷ�ó������
            if (ans!="���󣺳���Ϊ�㣡")
                JUDGE_ANS=true;
            break;
        }
        case 1:
        {
            return "���󣺲��������ã�";
        }
        case 2:
        {
            return "����Բ���Ų�ƥ�䣡";
        }
        case 3:
        {
            return "����������ʽ����";
        }
    }
    return ans;
}