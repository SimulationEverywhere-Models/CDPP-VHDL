

/*******************************************************************
*
*  DESCRIPTION: VHDL QuantumMultiply Model 
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
#ifndef __QUANTUMMULTIPLY_H 
#define __QUANTUMMULTIPLY_H

#include "atomic.h"


class QuantumMultiply : public Atomic
{
public:
    QuantumMultiply( const string &name = "QuantumMultiply" );//Default constructor

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
    
    Value Effective, attenuation;
    Time Transport_Delay;

};//class QuantumMultiply

// ** inline ** // 
inline
string QuantumMultiply::className() const
{
	return "QuantumMultiply" ;
}


#endif //__QUANTUMMULTIPLY_H
