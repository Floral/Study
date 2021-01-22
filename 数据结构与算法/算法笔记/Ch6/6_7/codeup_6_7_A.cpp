#include<cstdio>
#include<iostream>
#include<string>
#include<stack>

using namespace std;

int main()
{
    string line;

    while(getline(cin, line) && line!="0")
    {
        int op = 0;         //操作数
        bool flag = false;  //输入的是不是数字，false代表输入的是运算符
        char oper;          //运算符
        double result = .0; //最终答案
        stack<double> stOperand;    //操作数的栈
        stack<char> stOperator;     //运算符的栈
        int len = line.length();    //字符串长度

        for (int i = 0; i <= len; ++i)  //这里判断条件的等于号是为了保证处理完输入的最后一个数
        {
            if (line[i]>='0' && line[i]<='9')
            {
                op = op*10+line[i]-'0';
                flag = true;
            }else if (line[i] == '*' || line[i] == '/' || line[i] == '+' || line[i] == '-')
                oper = line[i];
            else if (line[i] == ' ' || line[i] == '\0') //输入完一个数或者运算符
            {
                //! 这数字可能是0，所以这么判断会出bug
                // if (op!=0)  //刚刚完成的是数字的输入
                if (flag)
                {
                    if (!stOperator.empty() && (stOperator.top()=='*' || stOperator.top()=='/'))
                    {   //如果前一个运算符是乘除，那么就先算出结果
                        double temp;
                        if (stOperator.top()=='*')
                            temp=(stOperand.top()*op);
                        else
                            temp=(1.0*stOperand.top()/op);
                        stOperator.pop();
                        stOperand.pop();
                        stOperand.push(temp);
                    }else
                        stOperand.push(op);
                    op = 0;
                    flag = false;
                }else   //刚刚完成的是运算符的输入
                    stOperator.push(oper);
            }
        }//完成上面的循环之后，运算符栈中只剩下加减法了
        stack<double> s1;   //翻转后的操作数栈
        stack<char> s2;     //翻转后的运算符栈
        while (!stOperator.empty())
        {
            s2.push(stOperator.top());
            stOperator.pop();
        }
        while (!stOperand.empty())
        {
            s1.push(stOperand.top());
            stOperand.pop();
        }
        double op1 = .0;
        double op2 = .0;
        char tempOp;
        while (!s2.empty()) //计算剩余的加减法
        {
            op1 = s1.top();
            s1.pop();
            op2 = s1.top();
            s1.pop();
            tempOp = s2.top();
            if (tempOp == '+')
                s1.push(op1+op2);
            else
                s1.push(op1-op2);

            s2.pop();
        }
        result = s1.top();
        s1.pop();
        printf("%.2f\n", result);
    }
    
    return 0;
}