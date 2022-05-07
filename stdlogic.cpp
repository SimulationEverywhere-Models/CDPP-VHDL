/*       Description: 1164 boolean operators *         *
*                                                      *
*        Author: Shaylesh Mehta     *                  *
*                                                      *
*        Email: skmehta@connectmail.carleton.ca      * *
*                                                      *
*        Date: October 19th 2002       *               *
******************************************************/

#include "stdlogic.h"


Value _1164not(Value a)
{
    int ia;
    ia=(int)a;
    switch (ia) {
    case 0:
        return (Value)(1);
    case 1:
        return (Value)(0);
    case 2:
        return (Value)(U);    
    case 3:
        return (Value)(U);    
    default:
        return (Value)(U);
    }
}

Value _1164and(Value a,Value b)
{
    int ia,ib,ic;
    ia = (int)a;
    ib = (int)b;
    
    if(ia>1 || ib>1)
        ic = U;
    else
        ic = (ia==1 && ib==1)?1:0;
    
    return (Value)(ic);
}

Value _1164or(Value a,Value b)
{
    int ia,ib,ic;
    ia = (int)a;
    ib = (int)b;
    
    if(ia>1 || ib>1)
        ic = U;
    else
        ic = (ia==1 || ib==1)?1:0;
    
    return (Value)(ic);
}

Value _1164xor(Value a,Value b)
{
    int ia,ib,ic;
    ia = (int)a;
    ib = (int)b;
    
    if(ia>1 || ib>1)
        ic = U;
    else
        ic = ((ia+ib)==1)?1:0;
    
    return (Value)(ic);
}

Value _1164nand(Value a,Value b)
{
    int ia,ib,ic;
    ia = (int)a;
    ib = (int)b;
    
    if(ia>1 || ib>1)
        ic = U;
    else
        ic = (ia==1 && ib==1)?0:1;
    
    return (Value)(ic);    
}

Value _1164nor(Value a,Value b)
{
    int ia,ib,ic;
    ia = (int)a;
    ib = (int)b;
    
    if(ia>1 || ib>1)
        ic = U;
    else
        ic = (ia==1 || ib==1)?0:1;
    
    return (Value)(ic);
}

Value _1164xnor(Value a,Value b)
{
    int ia,ib,ic;
    ia = (int)a;
    ib = (int)b;
    
    if(ia>1 || ib>1)
        ic = U;
    else
        ic = ((ia+ib)==1)?0:1;
    
    return (Value)(ic);
}

char sltochar(Value a)
{
    switch((int)a)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 3:
        return 'Z';
    case 4:
        return '-';
    default:
        return 'U';
    }
}
