
/*******************************************************************
*
*  DESCRIPTION: VHDL Process Model 
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
#ifndef __PROCESS_STAT_H 
#define __PROCESS_STAT_H

#include "atomic.h"


class Process : public Atomic
{
public:
    Process( const string &name = "Process" );//Default constructor

    virtual string className() const ;

protected:
    Model &internalFunction(const InternalMessage &) ;
    Model &initFunction() ;
    Model &externalFunction(const ExternalMessage &) ;
    Model &outputFunction(const InternalMessage &) ;
private:

    //port declarations, one input, one output

    const Port &clk, &d;
    Port &q;
    Value _d, _clk, _q;

};//class Process

// ** inline ** // 
inline
string Process::className() const
{
	return "Process" ;
}


#endif //__PROCESS_STAT_H
