#ifndef CALC_WIDGET_H
#define CALC_WIDGET_H
#define SMAX 1000

#include <QWidget>
#include <QStack>
#include "Qbolan.h"
#include "Calc.h"



/*-----------------------枚举按钮类型进行分类----------------*/
enum BtnType
{
    Num,   //数字
    Op,    //运算符
    Dot,   //点
    Equal, //等于
    Clear, //清空
    Back   //删除
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    friend class Qbolan;
    friend class Calc;

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


    static QString Bolan;

    //函数声明
    void ShowInText(QString&);            //显示
    void Backit(QString&);                //后退
    bool isDigit(QChar _c);               //是否数字

private:
    Ui::Widget *ui;


public slots:
    //按钮点击处理槽函数
    //根据按钮类型不同，将点击输入转成字符串
    void TodoClick(BtnType _type,QString _char);

};

#endif // CALC_WIDGET_H
