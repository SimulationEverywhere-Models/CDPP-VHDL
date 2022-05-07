/*       Description: Atomic Process Inv Model *         *
*                                                      *
*        Author: Shaylesh Mehta     *                  *
*                                                      *
*        Email: skmehta@connectmail.carleton.ca      * *
*                                                      *
*        Date: October 19th 2002       *               *
*******************************************************/

/* include files */

#include "message.h"
#include "mainsimu.h"
#include "process_stat_inv.h"
#include "stdlogic.h"
/* public functions */

Process_Inv :: Process_Inv( const string &name) 
: Atomic (name)
, in(addInputPort ("in"))   //constructors for input and output ports
, out(addInputPort("out"))

{
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &Process_Inv::initFunction()
{
    _in = 0;  //must have buffers for all triggers, inputs 
    _out = 0;
    holdIn(active,0);
    return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Process_Inv::externalFunction( const ExternalMessage &msg )
{
    Value sendOutput = 0;
    
    if (msg.port()==in) {  //since in is in the trigger list
        _in=msg.value();
        _out=_1164not(_in);
        sendOutput = 1;            
    }

    if(sendOutput)
        holdIn(active,0); // delta delay cycle, dont increment time
    
    return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Process_Inv::internalFunction( const InternalMessage & )
{
    passivate();   // always transition back to passive state
   
    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Process_Inv::outputFunction( const InternalMessage &msg )
{
    if(state()==active)
    {
        this->sendOutput(msg.time(),out,_out); //can add transport delay to msg.time
    }
    return *this ;
}


