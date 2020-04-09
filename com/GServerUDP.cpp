
// -*- mode: c++ -*-

#include "GServerUDP.h"
#include <logging/LLogApi.h>

using namespace LOGMASTER;


#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/types.h>

#ifndef  _WIN32
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#endif


#include <chrono>
#include <thread>
#include <time.h>

#include <unistd.h>

GServerUDP::GServerUDP()
{

}


GServerUDP::~GServerUDP()
{

}



#define MAXLINE 1024 /// CRAP PTH




#ifdef _WIN32
int
GServerUDP::Open(int)
{
	COM_FATAL("Not implemented for Windows");
	return -1;
}
#else
int
GServerUDP::Open( const int portno, const bool use_timout )
{
    COM_DEBUG("Opening port %d", portno );

    if ( (  fSocketFd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
    {
       perror("socket creation failed");
       fError.HandleError("failed to create socket", GLOCATION );
       return -1;
    }

    Init( &fServAddr, portno, "", use_timout  );
    // Init( &fServAddr, portno, "", false );

    if ( bind( fSocketFd, (const struct sockaddr *)&fServAddr,   sizeof(fServAddr)) < 0 )
    {
        fError.HandleError("failed to bind socket", GLOCATION );
        return -1;
    }

    while( fDoRun == true)
    {
        int n = 0;
        socklen_t len = 0;
        bzero(fBuffer, MAX_TCP_BUFFER_SIZE);
        n = recvfrom( fSocketFd, (char *)fBuffer, MAXLINE,  MSG_WAITALL, ( struct sockaddr *) &fReplAddr, &len);
        COM_INFO("Client, n = %d  bytes recieved , len = %d  buffer = %s", n, len,  fBuffer);

        if (n < 0) { continue; }

        string reply = HandleMessage(  fBuffer, n);

        n = sendto( fSocketFd, reply.c_str(), reply.size(),
               MSG_EOR, (const struct sockaddr *) &fReplAddr,  sizeof( fReplAddr ) );

        if (n < 0)
        {
            COM_ERROR("Error writing to socket");
            // fError.HandleError("ERROR writing to socket", GLOCATION);
        }

    } // end of endless loop

     return 0;
 }
#endif