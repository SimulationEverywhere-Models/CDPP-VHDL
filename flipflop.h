
/*******************************************************************
*
*  DESCRIPTION: Flip Flop
*
*  AUTHOR: Shaylesh Mehta
*
*  EMAIL: skmehta@connectmail.carleton.ca
*         
*
*  DATE: October 19th 2002
*
*******************************************************************/

#ifndef __FLIPFLOP_H
#define __FLIPFLOP_H

#include "atomic.h"


class FlipFlop : public Atomic
{
public:
    FlipFlop( const string &name = "FlipFlop" );					//Default constructor

    virtual string className() const ;

protected:
    Model &internalFunction(const InternalMessage &) ;
    Model &initFunction() ;
    Model &externalFunction(const ExternalMessage &) ;
    Model &outputFunction(const InternalMessage &) ;
private:

    //port declarations
    const Port &clk;
    const Port &d;
    Port &q;
    
    //internals declarations
    Value _d;
    Value _clk;
    Value _q;
    Time preparationTime;


};//class flipflop

// ** inline ** // 
inline
string FlipFlop::className() const
{
	return "FlipFlop" ;
}


#endif //__FLIPFLOP_H
