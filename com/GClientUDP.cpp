// -*- mode: c++ -*-


#include "GClientUDP.h"

#include <logging/LLogApi.h>

using namespace LOGMASTER;

#include <exception/GException.h>


#include <stdio.h>
#include <stdlib.h>


#include <string.h>
#include <sys/types.h>

#include <thread>
#include <chrono>


GClientUDP::GClientUDP()
{

}


GClientUDP::~GClientUDP()
{

}

int
GClientUDP::Open(   const string hostname,  const int portno, const bool use_timeout  )
{
    if( OpenSocket(SOCK_DGRAM ) < 0 )
    {
      return -1;
    }

    // Init( &fReplAddr,UDP_REPLY_PORT );
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    Init( &fServAddr, portno, hostname, use_timeout );

    return Bind();
}


