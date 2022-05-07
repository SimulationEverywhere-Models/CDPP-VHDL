
/*******************************************************************
*
*  DESCRIPTION: VHDL 4 bit counter process Model 
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
#ifndef __PROCESS_STAT_4_COUNTER_H 
#define __PROCESS_STAT_4_COUNTER_H

#include "atomic.h"


class Process_4_Counter : public Atomic
{
public:
    Process_4_Counter( const string &name = "Process_4_Counter" );//Default constructor

    virtual string className() const ;

protected:
    Model &internalFunction(const InternalMessage &) ;
    Model &initFunction() ;
    Model &externalFunction(const ExternalMessage &) ;
    Model &outputFunction(const InternalMessage &) ;
private:

    //port declarations, one input, one output

    const Port &clk, &d1, &d2, &d3, &d4;
    Port &q1,&q2,&q3,&q4;
    Value  _clk, _d1, _d2, _d3, _d4, _q1, _q2, _q3, _q4;

};//class Process

// ** inline ** // 
inline
string Process_4_Counter::className() const
{
	return "Process_4_Counter" ;
}


#endif //__PROCESS_STAT_4_COUNTER_H
