#include "calculator.h"
extern bool JUDGE_ANS;
bool JUDGE_ANS=false;
void counter::remove_space(string &exp)  //移除运算符和数字之间的空格，方便运算
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
                if (i!=exp.size() && judge_number(exp[i]))  return 3;//这里要特别判断一下，数字之间有空格也是非法。
            }
        }
        i++;
    }
    remove_space(exp);//移除所有空格，方便运算。
    //先判断有无操作符误用情况
    i=0;
    while (i<exp.size())
    {
        if (judge_operator(exp[i]))
        {
            if ((!judge_number(exp[i-1])) && exp[i]!='-' && exp[i-1]!=')')   return 1;
            //若运算符前一位不是数字 且 此运算符不为负号 且 前一位不为右括号，则有操作符误用
            if (!judge_number(exp[i+1]) && exp[i+1]!='(')    return 1;
            //若运算符后一位不是数字 且 不是左括号，则有操作符误用
        }
        //cout<<i-1<<endl<<exp[i-1]<<endl;
        if (exp[i]=='(' && i!=0 && judge_number(exp[i-1]))
            return 1; //判断有无 2(2*3) 这种隐藏乘号的错误
        if (exp[i]=='('&& exp[i+1]==')')//连续的括号也算错误
            return 1;
        i++;
    }
    i=0;
    //判断有无圆括号不匹配的情况
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
    //判断数字格式是否有误
    i=0;
    while (i<exp.size())
    {
        if (exp[i]=='.')
        {
            if (!judge_number(exp[i+1]))
                return 3;//若小数点后面不是数字，则报错
            if (judge_number(exp[i+1]) && judge_number(exp[i+2]))
                return 3;//若有两位小数也报错
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
            if (exp[i]=='-' && !(judge_number(exp[i-1])))//若有负数，则先补上一个0
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
                    return "错误：除数为零！";//在此处判断除数是否为0
                ans=op2/op1;
            }
            s.push(ans);
        }
        else
            s.push(stod(i));
    }
    ans_str=to_string(s.top());//因为to_string默认保留6位小数，所以要pop_back 5次
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
            ans=sub.calculate(sub.infix_to_suffix(exp));//因为判断除数为0在calculate里，
                                                        //因此需要一个全局变量判断是否正确得出结果。
            if (ans!="错误：除数为零！")
                JUDGE_ANS=true;
            break;
        }
        case 1:
        {
            return "错误：操作符误用！";
        }
        case 2:
        {
            return "错误：圆括号不匹配！";
        }
        case 3:
        {
            return "错误：数字形式错误！";
        }
    }
    return ans;
}