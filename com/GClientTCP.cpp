// -*- mode: c++ -*-


#include "GClientTCP.h"

#include <logging/LLogApi.h>

using namespace LOGMASTER;

#include <exception/GException.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>

#ifndef _WIN32
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif



GClientTCP::GClientTCP()
{

}


GClientTCP::~GClientTCP()
{

}

int
GClientTCP::Open(   const string hostname,  const int portno, const bool use_timeout  )
{
    if( OpenSocket(SOCK_STREAM ) < 0 )
    {
      return -1;
    }

    // Init( &fReplAddr, TCP_REPLY_PORT );
    // std::this_thread::sleep_for(std::chrono::milliseconds(2));
    Init( &fServAddr, portno, hostname,  use_timeout  );
    return Bind();

}



// void
// GClientTCP::Stop()
// {
//     fDoRun = false;
//     Close();
// }