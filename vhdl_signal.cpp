/*       Description: Atomic Signal Model              *
*                                                      *
*        Author: Shaylesh Mehta                        *
*                                                      *
*        Email: skmehta@connectmail.carleton.ca        *
*                                                      *
*        Date: October 19th 2002                       *
*******************************************************/

/* include files */

#include "message.h"
#include "mainsimu.h"
#include "vhdl_signal.h"

/* public functions */

Signal :: Signal( const string &name) 
: Atomic (name)
, in(addInputPort ("in"))   //constructors for input and output ports
, out(addInputPort("out"))
, Transport_Delay( 0, 0, 0, 0)
{
    string time( MainSimulator::Instance().getParameter( description(), "Transport_Delay" ) );
    if (time != "") {
        Transport_Delay = time;
    }
}


/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &Signal::initFunction()
{
    Effective = 0 ;
    return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Signal::externalFunction( const ExternalMessage &msg )
{
    if (msg.port()==in) {    
        
        if(Effective!=msg.value()); // this is assuming that transport delay in external message delays meesage by time
        {
            Effective = msg.value() ;
            holdIn(active,Transport_Delay);
        }
    }
    
    return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Signal::internalFunction( const InternalMessage & )
{
    passivate();   // always transition back to passive state
   
    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Signal::outputFunction( const InternalMessage &msg )
{
    if(state()==active)
    {
        this->sendOutput(msg.time(),out,Effective); 
    }
    return *this ;
}


