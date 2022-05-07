/*       Description: 1164 boolean operators *         *
*                                                      *
*        Author: Shaylesh Mehta     *                  *
*                                                      *
*        Email: skmehta@connectmail.carleton.ca      * *
*                                                      *
*        Date: October 19th 2002       *               *
*******************************************************/



#ifndef __1164Bool__
#define __1164Bool__

#include "Value.h"

enum std_logic {Zero,One,Z,DC,U};

Value _1164not(Value);
Value _1164and(Value,Value);
Value _1164or(Value,Value);
Value _1164xor(Value,Value);
Value _1164nand(Value,Value);
Value _1164nor(Value,Value);
Value _1164xnor(Value,Value);

char sltochar(Value);

#endif
