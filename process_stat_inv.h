
/*******************************************************************
*
*  DESCRIPTION: VHDL Process_Inv Model 
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
#ifndef __PROCESS_STAT_INV_H 
#define __PROCESS_STAT_INV_H

#include "atomic.h"


class Process_Inv : public Atomic
{
public:
    Process_Inv( const string &name = "Process_Inv" );//Default constructor

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
    Value _in, _out;

};//class Process_Inv

// ** inline ** // 
inline
string Process_Inv::className() const
{
	return "Process_Inv" ;
}


#endif //__PROCESS_STAT_INV_H
