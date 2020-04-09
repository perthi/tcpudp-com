// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include "GServerTCPPublisher.h"
#include <logging/LLogApi.h>

using namespace LOGMASTER;

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


#include <chrono>
#include <thread>


GServerTCPPublisher::GServerTCPPublisher()
{

}

GServerTCPPublisher::~GServerTCPPublisher()
{

}


int 
GServerTCPPublisher::Open( const int portno, const bool use_timeout)
{
    COM_INFO("Opening port %d", portno);

    if (fSocketFd != 0)
    {
        close(fSocketFd);
        fSocketFd = 0;
    }
    
    fSocketFd = -1;
    fNewfSocketFd = -1;

    socklen_t clilen; 

    while( fSocketFd < 0  )
    {

        fSocketFd = socket(AF_INET, SOCK_STREAM, 0);
        Init(&fServAddr, portno, "", use_timeout);

        if (fSocketFd < 0)
        {
            FORCE_DEBUG("port = %d", portno );
            fError.HandleError("ERROR opening socket", GLOCATION);
        }

        if (bind(fSocketFd, (struct sockaddr *)&fServAddr, sizeof(fServAddr)) < 0)
        {
            fError.HandleError("Error on binding", GLOCATION);
        }
        std::this_thread::sleep_for( std::chrono::milliseconds(100));

        listen(fSocketFd, 5);
      

    }

    while( fNewfSocketFd  < 0  )
    {
        clilen = sizeof(fReplAddr);
        fNewfSocketFd = accept(fSocketFd, (struct sockaddr *)&fReplAddr, &clilen);
        std::this_thread::sleep_for( std::chrono::milliseconds(100));
    }




    FORCE_DEBUG("OPENED SOCKET !!!!!!!( fSocketFd = %d, fNewfSocketFd = %d )",  fSocketFd, fNewfSocketFd  );

    // listen(fSocketFd, 5);
    // socklen_t clilen = sizeof(fReplAddr);
    // fNewfSocketFd = accept(fSocketFd, (struct sockaddr *)&fReplAddr, &clilen);
 
    return 0;
}


int
GServerTCPPublisher::Close()
{
    close( fNewfSocketFd);
    close(fSocketFd);
    return 0;
}


int 
GServerTCPPublisher::Write(const string msg)
{
    int n = write(fNewfSocketFd, msg.c_str(), msg.size());

    FORCE_DEBUG( "fSocketFd = %d, fNewfSocketFd = %d",  fSocketFd, fNewfSocketFd  );

    if (n < 0)
    {
        fError.HandleError("ERROR writing to socket", GLOCATION);
        return -1;
    }

    return 0;

}