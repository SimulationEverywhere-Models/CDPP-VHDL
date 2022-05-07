
/*       Description: Atomic qsubtract Model           *
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
#include "qsubtract.h"

/* public functions */

qsubtract :: qsubtract( const string &name) 
: Atomic (name)
, ipos(addInputPort ("ipos"))   //constructors for input and output ports
, ineg(addInputPort ("ineg"))
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
Model &qsubtract::initFunction()
{
    _ipos = 0;
    _ineg = 0;
    return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &qsubtract::externalFunction( const ExternalMessage &msg )
{
    if (msg.port()==ipos) {    
        
        _ipos = msg.value();
        
        holdIn(active,Transport_Delay);
    }
    
    if (msg.port()==ineg) {    
        
        _ineg = msg.value();
        
        holdIn(active,Transport_Delay);
    }

    
    return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &qsubtract::internalFunction( const InternalMessage & )
{
    passivate();   // always transition back to passive state
   
    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &qsubtract::outputFunction( const InternalMessage &msg )
{
    if(state()==active)
    {
        this->sendOutput(msg.time(),out,(_ipos - _ineg)); 
    }
    return *this ;
}


