

/*******************************************************************
*
*  DESCRIPTION: VHDL rkIntegModel Model 
*
*  AUTHOR: Shaylesh Mehta
*
*  EMAIL: skmehta@connectmail.carleton.ca
*         
*
*  DATE: November 16th 2002
*
*******************************************************************/

// prevent multiple inclusion with preprocessor directive
#ifndef __rkIntegModel_H 
#define __rkIntegModel_H

#include "atomic.h"


class rkIntegModel : public Atomic
{
public:
    rkIntegModel( const string &name = "rkIntegModel" );//Default constructor

    virtual string className() const ;

protected:
    Model &internalFunction(const InternalMessage &) ;
    Model &initFunction() ;
    Model &externalFunction(const ExternalMessage &) ;
    Model &outputFunction(const InternalMessage &) ;
private:

    //port declarations, one input, one output

    const Port &dydt, &vin;
    Port &y;
    
    Value HoldTime;
    Value _y, _dydt,_vin;
    Value h1,h2,h3,h4,d,p1,p2,p3,p4,C,R,ytemp,total;
    
    FILE *fp;
};//class rkIntegModel

// ** inline ** // 
inline
string rkIntegModel::className() const
{
	return "rkIntegModel" ;
}


#endif //__rkIntegModel_H
