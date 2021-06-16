#ifndef QBOLAN_H
#define QBOLAN_H

#include <QStack>
#include <QString>

class Qbolan
{
public:
    Qbolan();
    /*_______________________________________________*/
    static QString QBolan(QString& , int(*fp)(QChar));
    /*_______________________________________________*/
    static int Priority(QChar c);
};

#endif // QBOLAN_H
