/*       Description: Atomic 4 bit counter Model *         *
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
#include "process_stat_4_counter.h"
#include "stdlogic.h"

/* public functions */

Process_4_Counter :: Process_4_Counter( const string &name) 
: Atomic (name)
, clk(addInputPort ("clk"))   //constructors for input and output ports
, d1(addInputPort("d1"))
, d2(addInputPort("d2"))
, d3(addInputPort("d3"))
, d4(addInputPort("d4"))
, q1(addOutputPort("q1"))
, q2(addOutputPort("q2"))
, q3(addOutputPort("q3"))
, q4(addOutputPort("q4"))
{
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &Process_4_Counter::initFunction()
{
    _clk = 0;
    _d1 = 0;  //must have buffers for all triggers, inputs 
    _d2 = 0;
    _d3 = 0;
    _d4 = 0;
    _q1 = 0;
    _q2 = 0;
    _q3 = 0;
    _q4 = 0;

    holdIn(active,0);

    return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Process_4_Counter::externalFunction( const ExternalMessage &msg )
{
    Value sendOutput = 0;
    
        if (msg.port()==d1) {    
            _d1=msg.value(); //buffer inputs to processes
        }
        if (msg.port()==d2) {    
            _d2=msg.value(); //buffer inputs to processes
        }
        if (msg.port()==d3) {    
            _d3=msg.value(); //buffer inputs to processes
        }
        if (msg.port()==d4) {    
            _d4=msg.value(); //buffer inputs to processes
        }

        if (msg.port()==clk) {  //since clk is in the trigger list
            
                if(msg.value() && !_clk) { // if rising_edge(clk)           
                    
                    _q1=_1164not(_d1);
                    _q2=_1164xor(_d2,_d1);
                    _q3=_1164xor(_d3,_1164and(_d1,_d2));
                    _q4=_1164xor(_d4,_1164and(_d3,_1164and(_d1,_d2)));
                    
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
Model &Process_4_Counter::internalFunction( const InternalMessage & )
{
    passivate();   // always transition back to passive state
   
    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Process_4_Counter::outputFunction( const InternalMessage &msg )
{
    if(state()==active)
    {
        this->sendOutput(msg.time(),q1,_q1); //can add transport delay to msg.time
        this->sendOutput(msg.time(),q2,_q2);
        this->sendOutput(msg.time(),q3,_q3);
        this->sendOutput(msg.time(),q4,_q4);
    }
    return *this ;
}


