
/*       Description: Atomic QuantumMultiply Model              *
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
#include "QuantumMultiply.h"

/* public functions */

QuantumMultiply :: QuantumMultiply( const string &name) 
: Atomic (name)
, in(addInputPort ("in"))   //constructors for input and output ports
, out(addInputPort("out"))
, Transport_Delay( 0, 0, 0, 0)
{
    string s1;

    string time( MainSimulator::Instance().getParameter( description(), "Transport_Delay" ) );
    if (time != "") {
        Transport_Delay = time;
    }

    if((s1=MainSimulator::Instance().getParameter(description(), "Attenuation"))=="")
        attenuation=1.0;
    else
        attenuation=atof(s1.c_str());
}


/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &QuantumMultiply::initFunction()
{
    Effective = 0 ;
    return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &QuantumMultiply::externalFunction( const ExternalMessage &msg )
{
    if (msg.port()==in) {    
        
            Effective = msg.value() * attenuation ;
            holdIn(active,Transport_Delay);
        
    }
    
    return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &QuantumMultiply::internalFunction( const InternalMessage & )
{
    passivate();   // always transition back to passive state
   
    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &QuantumMultiply::outputFunction( const InternalMessage &msg )
{
    if(state()==active)
    {
        this->sendOutput(msg.time(),out,Effective); 
    }
    return *this ;
}


