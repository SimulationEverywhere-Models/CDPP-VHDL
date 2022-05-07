
/*       Description: Atomic rkIntegModel Model        *
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
#include "rkIntegModel.h"
#include "AnalogDef.h"
#include "mathincl.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* public functions */

rkIntegModel :: rkIntegModel( const string &name) 
: Atomic (name)
, dydt(addInputPort ("dydt"))   //constructors for input and output ports
, vin(addInputPort ("vin"))
, y(addOutputPort("y"))
{
    string s1,s2,s3,s4;

    if((s1=MainSimulator::Instance().getParameter(description(), "y0" ))=="")
        _y=0.0;
    else
        _y=atof(s2.c_str());

    if((s2=MainSimulator::Instance().getParameter(description(), "dydt0" ))=="")
        _dydt=0.0;
    else
        _dydt=atof(s3.c_str());   
    
    if((s3=MainSimulator::Instance().getParameter(description(), "C" ))=="")
        C=1.0E-5;
    else
        C=atof(s3.c_str());

    if((s4=MainSimulator::Instance().getParameter(description(), "R" ))=="")
        R=1000.0;
    else
        R=atof(s4.c_str());

}       


/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &rkIntegModel::initFunction()
{
    //set initial values for port buffers and constant
    
    //fp=fopen("test.log","w");
    
    HoldTime = 0; 
    total = 0;
    holdIn(active,(float)HoldTime); //send out inital value
    _vin=0;
    
    fp=fopen("decay.out","w");

    return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &rkIntegModel::externalFunction( const ExternalMessage &msg )
{
    
    if (msg.port()==dydt) 
    {    
        _dydt=(int)msg.value();        
    }
    
    if(msg.port()==vin)
    {
        _vin=(int)msg.value();
    }
        
    if(state()!=active)
    {
        
        //evaluate integral
        
        p1 = (1.0/(C*R))*(_vin*QuantumSize - (_dydt*QuantumSize));
        p2 = (1.0/(C*R))*(_vin*QuantumSize - (_dydt*QuantumSize + sign(p1)*(HalfQuantumSize/2.0)));
        p3 = (1.0/(C*R))*(_vin*QuantumSize - (_dydt*QuantumSize + sign(p2)*(HalfQuantumSize/2.0)));
        p4 = (1.0/(C*R))*(_vin*QuantumSize - (_dydt*QuantumSize + sign(p2)*(HalfQuantumSize)));
        
        //printf("C %f R %f 1/CR : %f p %f %f %f %f\n",C,R,(1.0/(C*R)),p1,p2,p3,p4);

        h1 = HalfQuantumSize / p1;
        h2 = HalfQuantumSize / p2;
        h3 = HalfQuantumSize / p3;
        h4 = HalfQuantumSize / p4;

        d = 1.0/(6.0*h1) + 1.0/(3.0*h2) + 1.0/(3.0*h3) + 1.0/(6.0*h4);

        if(p1!=0.0 && d!=0.0)
        {
            
            HoldTime = fabs(1.0/d) * TimebaseScaler;
            //printf("%f %f\n",HoldTime,d);
            ytemp=sign(p1);
            total+=HoldTime;
            fprintf(fp,"%f %f %f\n",total,_y*QuantumSize,_dydt*QuantumSize);
            holdIn(active,(float)HoldTime);
            
        }
        else
        {
            passivate();
        
        }
    
    }
    return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &rkIntegModel::internalFunction( const InternalMessage & )
{           
    _y+=sign(ytemp); // increment/decrement quantum
    passivate();
    return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &rkIntegModel::outputFunction( const InternalMessage &msg )
{
    if(state()==active)
    {
        this->sendOutput(msg.time(),y,_y+sign(ytemp));     
    }
    return *this ;
}


