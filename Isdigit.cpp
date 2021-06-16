#include "Isdigit.h"

IsDigit::IsDigit()
{

}

bool isDigit(QChar _a)
{
    if(_a >= '0' && _a <= '9')
        return true;
    else
        return false;
}
