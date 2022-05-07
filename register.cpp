/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "generat.h"    // class Generator
#include "flipflop.h"
#include "process_stat_4_counter.h"
#include "process_stat.h"   // class process
#include "process_stat_inv.h"
#include "qsubtract.h"
#include "QuantumMultiply.h"
#include "rkIntegModel.h"
#include "vhdl_signal.h"


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<FlipFlop>() , "FlipFlop" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Process_4_Counter>() , "Process_4_Counter" ) ;    
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Process_Inv>() , "Process_Inv" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Process>() , "Process" ) ;
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<qsubtract>() , "qsubtract" ) ;    
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<QuantumMultiply>() , "QuantumMultiply" ) ;    
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<rkIntegModel>() , "rkIntegModel" ) ;    
    SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Signal>() , "Signal" ) ;
}
