#include "Calc_Widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //窗口创建时，初始化存放逆波兰表达式的Bolan字符串
    QString Bolan = "";


    //处理点击输入信号,并在显示框内显示
    /*------------------------------------数---------------------------------------*/
    connect(ui->num0,&QPushButton::clicked,[this]()->void{TodoClick(Num,"0");});//按钮0
    connect(ui->num1,&QPushButton::clicked,[this]()->void{TodoClick(Num,"1");});//按钮1
    connect(ui->num2,&QPushButton::clicked,[this]()->void{TodoClick(Num,"2");});//按钮2
    connect(ui->num3,&QPushButton::clicked,[this]()->void{TodoClick(Num,"3");});//按钮3
    connect(ui->num4,&QPushButton::clicked,[this]()->void{TodoClick(Num,"4");});//按钮4
    connect(ui->num5,&QPushButton::clicked,[this]()->void{TodoClick(Num,"5");});//按钮5
    connect(ui->num6,&QPushButton::clicked,[this]()->void{TodoClick(Num,"6");});//按钮6
    connect(ui->num7,&QPushButton::clicked,[this]()->void{TodoClick(Num,"7");});//按钮7
    connect(ui->num8,&QPushButton::clicked,[this]()->void{TodoClick(Num,"8");});//按钮8
    connect(ui->num9,&QPushButton::clicked,[this]()->void{TodoClick(Num,"9");});//按钮9
    /*----------------------------------运算符---------------------------------------*/
    connect(ui->Sum,&QPushButton::clicked,[this]()->void{TodoClick(Op,"+");});//按钮+
    connect(ui->Sub,&QPushButton::clicked,[this]()->void{TodoClick(Op,"-");});//按钮-
    connect(ui->Mul,&QPushButton::clicked,[this]()->void{TodoClick(Op,"*");});//按钮*
    connect(ui->Div,&QPushButton::clicked,[this]()->void{TodoClick(Op,"/");});//按钮/
    /*----------------------------------操作符---------------------------------------*/
    connect(ui->Equal,&QPushButton::clicked,[this]()->void{TodoClick(Equal,"=");});//按钮=
    connect(ui->Clear,&QPushButton::clicked,[this]()->void{TodoClick(Clear,"C");});//按钮Clear
    connect(ui->Back,&QPushButton::clicked,[this]()->void{TodoClick(Back,"B");});//按钮Back
    connect(ui->Dot,&QPushButton::clicked,[this]()->void{TodoClick(Dot,".");});//按钮.


}

Widget::~Widget()
{
    delete ui;
}

//点击生成字符串
void Widget::TodoClick(BtnType _type,QString _char)
{
    static QString fromula = "";               //公式字符串
    //制定公式的语法规则，并压入字符串
    switch (_type)
    {
        //数字直接压入字符串
        case Num:
        {
            fromula += _char;
            ShowInText(fromula);
            break;
        }
        //操作符在非空且前一个为是数时压入
        case Op:
        {
            //非空,数后
            if(!fromula.isEmpty() && isDigit(fromula[fromula.length()-1]))
            {
                fromula += _char;
                ShowInText(fromula);
            }
            break;
        }
        //小数点在数之间 且数之间只允许一个小数点 时压入
        case Dot:
        {
            //判断数中是否有小数点
            bool nohave = true;
            //遍历起点
            int i = fromula.length()-2;
            //非空，数间
            if(!fromula.isEmpty() && isDigit(fromula[fromula.length()-1]))
            {
                //遍历判断每个数是否有小数点，是录入.否不录
                while(nohave && i >= 0)
                {
                    if(fromula[i] == '.')
                    {
                        nohave = false;
                    }
                    else if(fromula[i] == '+'|| fromula[i] == '-'|| fromula[i] == '*'|| fromula[i] == '/')
                    {
                        break;
                    }
                    else
                    {
                        i--;
                    }

                }
                //数中不存在小数点压入
                if(nohave)
                {
                    fromula += _char;
                    ShowInText(fromula);
                }

            }
            break;
        }
        //清空操作
        case Clear:
        {
            fromula.clear();
            ShowInText(fromula);
            break;
        }
        //后退操作
        case Back:
        {
            Backit(fromula);
            ShowInText(fromula);
            break;
        }
        //计算
        case Equal:
        {
            //判断最后一个输入的是否为运算符，是=无效 否继续
            if(fromula[fromula.length()-1] == '+'|| fromula[fromula.length()-1] == '-'|| fromula[fromula.length()-1] == '*'|| fromula[fromula.length()-1] == '/')
                break;
            //和存放地点
            double sum = 0.0;
            //逆波兰
            QString str = Qbolan::QBolan(fromula,Qbolan::Priority);
            //计算函数
            sum = Calc::doCalc(str);
            //数转字符
            QString end = QString::number(sum);
            //输出
            ui->LineEdit->setText(end);
            str.clear();
            break;
        }
    }
}

//显示函数
void Widget::ShowInText(QString& _fromula)
{
    ui->LineEdit->setText(_fromula);
}
void Widget::Backit(QString& _fromula)
{
    _fromula.chop(1);
}
bool Widget::isDigit(QChar _c)
{
    if(_c >= '0' && _c <= '9')
        return true;
    else
        return false;
}
