/*       Description: Atomic Flip Flop Model *         *
*                                                      *
*        Author: Shaylesh Mehta     *                  *
*                                                      *
*        Email: skmehta@connectmail.carleton.ca      * *
*                                                      *
*        Date: October 19th 2002       *               *
*******************************************************/

/* This model simulates a flip flop, but has been written such that the                                  *
*  form may be reused to code any sAMS-VHDL process. Processes do not have output                        *
*  events until they have executed all commands in their process body, and as such                       *
*  this model will execute statements triggered in the process and output events within                  *
*  1 preparation time. Output events will occur concurrently with respect to simulation time,            *
*  and will only be output on a change in the output port value.                                                                     *
*                                                                                                        *
*  ports must exist for all signals (read/modified) and all sensitivity list items.                      *
*  local buffer variables will exist for each of these ports. read signals and sensitivity list items    *
*  will become input ports, modified signals will become output ports. The drivers for all               *
*  output ports will be identified.                                                                      *
*                                                                                                        *
*  external events on read signal ports will be buffered locally. external events on sensitivity         *
*  list items will run the process body and any changes on the drivers for an output port will           *
*  transition the model to the active state for 1 preptime. Upon transition from active to passive       *
*  an output event will be triggered, the drivers of output ports will be checked against the current    *
*  buffered value of the output port, if it is different, the output port buffer is assigned it's driver *
*  and an output event is generated on the output port with the value of the buffer.                     *
*********************************************************************************************************/

/* process (clk)            *  clk is a trigger
*  begin                    *
*      if(rising_edge(clk)) *
*      {                    *
*          q<=d;            * d is a read signal
*      }                    * q is a modified signal, d is the driver for q
*  end process;             *
****************************/

/* Ports: *
*         *
*  clk    *
*  d      *
*  q      *
**********/
 
 
/* include files */

#include "message.h"
#include "mainsimu.h"
#include "flipflop.h"

/* public functions */

FlipFlop :: FlipFlop( const string &name) 
: Atomic (name)
, clk(addInputPort ("clk"))   //constructors for input and output ports
, d(addInputPort("d"))
, q(addOutputPort("q"))
, preparationTime (0,0,1,0)  //constructor for time
{
    string time(MainSimulator::Instance().getParameter ( description(), "preparation"));
    if(time != "")
        preparationTime = time;
}
/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &FlipFlop::initFunction()
{
    _d = 0;  //must have buffers for all triggers, inputs, outputs of process 
    _q = 0;
    _clk = 0;
    
    return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &FlipFlop::externalFunction( const ExternalMessage &msg )
{
    Value OutputEvent=0;

    if (msg.port()==d) {    
        _d=msg.value(); //buffer inputs to processes
    }
    
    if (msg.port()==clk) {  //since clk is in the trigger list
        
            if(msg.value() && !_clk) { // if rising_edge(clk)
                
                //since output has to be modified              
                // q<=d;                                       
                // if d were some boolean statement            
                // a intermediate driver variable would be     
                // created as the result of that statement     
                // and that would be the driver for the output.
                // buffer triggers to process                  
                
                OutputEvent=1;              
                _clk=msg.value();           
            }
        
    }

//since more than 1 output may be modified, this must be placed
// at the end of the function to transition to the appropriate state   

// this is also meccessary because processes do not output until all
// sequential statements in the process body are executed.

     if(OutputEvent){                      
     
         holdIn(active,preparationTime); 
         printf("output event\n");
     }
     else                                  
         passivate();                    
     

    return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &FlipFlop::internalFunction( const InternalMessage & )
{
	passivate();   // always transition back to passive state
	printf("internal x-ition\n");
    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &FlipFlop::outputFunction( const InternalMessage &msg )
{
    if(_q!=_d)   // only send output events if change has occured
    {            // on driver for output
        _q=_d;
        printf("sending output d:%d\n",_q);
        sendOutput( msg.time(), q, _q) ;  //send output events
    }
    return *this ;
}


