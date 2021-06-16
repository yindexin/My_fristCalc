#include "Qbolan.h"

Qbolan::Qbolan()
{

}
//设置运算符优先级
int Qbolan::Priority(QChar _c)
{
    switch (_c.unicode())
    {
    case '+' :
    {
        return 1;
    }
    case '-' :
    {
        return 1;
    }
    case '*' :
    {
        return 2;
    }
    case '/' :
    {
        return 2;
    }
    case '%' :
    {
        return 2;
    }
    default:return 0;
    }
}
//逆波兰表达式
QString Qbolan::QBolan(QString& _f,int(*fp)(QChar))
{
    //逆波兰字符串
    static QString Bolan;
    //运算符栈，用来判断运算符出现在逆波兰的位置
    QStack<QChar> opStact;
    //遍历正常式子
    for (int i=0;i<_f.length();i++)
    {
        QChar ch = _f[i];
        //这个是数进行拼接，下个是运算符拼接空格
        if(ch<='9'&&ch>='0')
        {
            Bolan += ch;
            if(_f[i+1] == '+' ||_f[i+1] == '-' ||_f[i+1] == '*' ||_f[i+1] == '/' ||_f[i+1] == '%')
                Bolan += ' ';
        }
        //这个是.进行拼接
        else if (ch == '.')
        {
            Bolan += ch;
        }
        //遇到括号，左括号作为标记入栈，但遇到右括号将所有在左括号之上的，全部拼接
        else if (ch == '(')
        {
            opStact.push(ch);
        }
        else if (!opStact.isEmpty() && ch == ')')
        {
            while (opStact.top() != '(' )
            {
               Bolan += opStact.top();
               opStact.pop();
            }
            opStact.pop();
        }
        //如果遇到的是运算符，按照如下规则操作
        else
        {
             //如果运算符栈不为空
            if(!opStact.empty())
            {
                //当前的优先级比栈中的高，当前的入栈
                if(fp(ch) > fp(opStact.top()))
                    opStact.push(ch);
                //当前的优先级比栈顶的低或相同时进行 遍历，为当前找到适和的位置
                else
                {
                    while (!opStact.empty())
                    {
                        //只要比当前优先后相同的全都优先拼接
                        if((fp(ch) <= fp(opStact.top())))
                        {
                            Bolan += opStact.top();
                            opStact.pop();
                        }
                        //直到最后退出
                        else
                            break;
                    }
                    //当前入栈
                    opStact.push(ch);
                }

            }
            //刚开始直接压入
            else
            {
                opStact.push(ch);
            }
        }
    }
    //最后将其余运算符拼接
    while (!opStact.empty())
    {
        Bolan += opStact.top();
        opStact.pop();
    }
    return Bolan;
}
