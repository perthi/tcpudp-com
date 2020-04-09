// -*- mode: c++ -*-
#ifndef GSERVERUDPRELAY_H
#define GSERVERUDPRELAY_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "GServerUDP.h"
#include <functional>

#include <vector>

using std::vector;


class  GServerUDPRelay : public  GServerUDP
{
	public:
		GServerUDPRelay();
		virtual ~GServerUDPRelay();
		virtual string API  HandleMessage(const string msg) override ;
		void UpdateSubscribers(  const string msg  ) const;
		void RegisterSubscriber(  void(  *funct)(const  string msg  ));

private:
	  static vector< void(*)(const string msg   ) > fSubscribers;

};

#endif
