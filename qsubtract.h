

/*******************************************************************
*
*  DESCRIPTION: VHDL qsubtract Model 
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
#ifndef __QSUBTRACT__ 
#define __QSUBTRACT__

#include "atomic.h"


class qsubtract : public Atomic
{
public:
    qsubtract( const string &name = "qsubtract" );//Default constructor

    virtual string className() const ;

protected:
    Model &internalFunction(const InternalMessage &) ;
    Model &initFunction() ;
    Model &externalFunction(const ExternalMessage &) ;
    Model &outputFunction(const InternalMessage &) ;
private:

    //port declarations, one input, one output

    const Port &ipos, &ineg;
    Port &out;
    
    Value _ipos,_ineg;
    Time Transport_Delay;

};//class qsubtract

// ** inline ** // 
inline
string qsubtract::className() const
{
	return "qsubtract" ;
}


#endif //__QSUBTRACT_H
