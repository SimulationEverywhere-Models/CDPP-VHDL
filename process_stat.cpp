/*       Description: Atomic Flip Flop Model *         *
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
#include "process_stat.h"

/* public functions */

Process :: Process( const string &name) 
: Atomic (name)
, clk(addInputPort ("clk"))   //constructors for input and output ports
, d(addInputPort("d"))
, q(addOutputPort("q"))
{
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &Process::initFunction()
{
    _d = 0;  //must have buffers for all triggers, inputs 
    _clk = 0;
    _q = 0;
    return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Process::externalFunction( const ExternalMessage &msg )
{
    Value sendOutput = 0;
    
        if (msg.port()==d) {    
            _d=msg.value(); //buffer inputs to processes
        }
    
        if (msg.port()==clk) {  //since clk is in the trigger list
            
                if(msg.value() && !_clk) { // if rising_edge(clk)           
                    _q=_d;
                    sendOutput = 1;            
                }
                _clk=msg.value();
        }

        if(sendOutput)
            holdIn(active,0); // delta delay cycle, dont increment time
   

    return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Process::internalFunction( const InternalMessage & )
{
    passivate();   // always transition back to passive state
   
    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Process::outputFunction( const InternalMessage &msg )
{
    if(state()==active)
    {
        this->sendOutput(msg.time(),q,_q); //can add transport delay to msg.time
    }
    return *this ;
}


