#include "Calc.h"

Calc::Calc()
{

}
double Calc::doCalc (QString f)
{
    //运算栈，根据逆波兰 遇数压入，与运算符提数运算
    QStack<double> calc;
    //初始化字符转数的运算空间
    QString num = "";
    //char 单个字符读入
    QChar ch;
    //初始化中间变量
    double a = 0.0,b = 0.0,sum=0.0;
    //遍历字符
    for (int i = 0;i<f.length();i++)
    {
        ch = f[i];
        //是数字拼接
        if(ch <= '9' && ch >= '0')
        {
            num += ch;
        }
        //是小数点拼接
        else if (ch == '.')
        {
            num += ch;
        }
        //遇到空格 即已经得到一个完整的数 入栈
        else if (ch == ' ')
        {
            calc.push(num.toDouble());
            num = "";
        }
        //运算符
        else
        {
            //运算符前是数字 说明数已经完整，入栈
            if(f[i-1] <= '9' && f[i-1] >= '0')
            {
                calc.push(num.toDouble());
                num = "";
            }
            //开始运算
            switch (ch.unicode())
            {
                case '+':
                {
                    //获取栈顶元素并出栈 进行两数运算
                    a = calc.top();calc.pop();
                    b = calc.top();calc.pop();
                    //先入栈的为被运算数
                    calc.push(b+a);
                    break;
                }
                case '-':
                {
                    a = calc.top();calc.pop();
                    b = calc.top();calc.pop();
                    calc.push(b-a);
                    break;
                }
                case '*':
                {
                    a = calc.top();calc.pop();
                    b = calc.top();calc.pop();
                    calc.push(b*a);
                    break;
                }
                case '/':
                {
                    a = calc.top();calc.pop();
                    b = calc.top();calc.pop();
                    calc.push(b/a);
                    break;
                }
            }
        }
    }
    //结果出栈
    sum = calc.top();calc.pop();
    return sum;
}
