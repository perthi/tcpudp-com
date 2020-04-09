// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "GServerUDPRelay.h"
#include <logging/LLogApi.h>
using namespace LOGMASTER;

vector< void(*)(const string msg   ) >   GServerUDPRelay::fSubscribers;


GServerUDPRelay::GServerUDPRelay()
{

}


GServerUDPRelay::~GServerUDPRelay()
{

}
 


string 
GServerUDPRelay::HandleMessage(const string msg)
{
   // FORCE_DEBUG("Hello world from UDP RELAY !!!!!, msg = %s", msg.c_str() );
    UpdateSubscribers("Hellow worls form callback function, msg = " + msg  );
    return "blahhhh";
}



void 
GServerUDPRelay::UpdateSubscribers(  const string msg  ) const
{
    for( size_t i=0; i <  fSubscribers.size();  i++  )
    {
        void(  *funct)(const  string )  =  fSubscribers.at(i);
        funct( msg );  
    }


}


void 
GServerUDPRelay::RegisterSubscriber(  void(  *funct)(const  string msg  ))
{
   fSubscribers.push_back(funct);

}


