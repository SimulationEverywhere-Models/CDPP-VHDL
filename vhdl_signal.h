
/*******************************************************************
*
*  DESCRIPTION: VHDL Signal Model 
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
#ifndef __SIGNAL_H 
#define __SIGNAL_H

#include "atomic.h"


class Signal : public Atomic
{
public:
    Signal( const string &name = "Signal" );//Default constructor

    virtual string className() const ;

protected:
    Model &internalFunction(const InternalMessage &) ;
    Model &initFunction() ;
    Model &externalFunction(const ExternalMessage &) ;
    Model &outputFunction(const InternalMessage &) ;
private:

    //port declarations, one input, one output

    const Port &in;
    Port &out;
    
    Value Effective;
    Time Transport_Delay;

};//class Signal

// ** inline ** // 
inline
string Signal::className() const
{
	return "Signal" ;
}


#endif //__SIGNAL_H
