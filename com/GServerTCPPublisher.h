// -*- mode: c++ -*-
#ifndef GSERVERTCPPUBLISHER_H
#define GSERVERTCPPUBLISHER_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/


#include "GServerTCP.h"


class  GServerTCPPublisher : public GServerTCP
{
	public:
		GServerTCPPublisher();
		virtual ~GServerTCPPublisher();
		virtual int API  Open( const int portno, const bool use_timout = true) override;
		int fNewfSocketFd = 0;
		virtual int Write( const string msg ) override;
		virtual int Close() override;
};

#endif
