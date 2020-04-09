
// -*- mode: c++ -*-

#include "GServerTCP.h"
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


GServerTCP::GServerTCP() 
{

}


GServerTCP::~GServerTCP()
{

}


#ifdef _WIN32
int
GServerTCP::Open(int)
{
	COM_FATAL("Not implemented for Windows");
	return -1;
}
#else
int GServerTCP::Open(const int portno, const bool use_timeout)
{
    COM_INFO("Opening port %d", portno);

    if (fSocketFd != 0)
    {
        close(fSocketFd);
        fSocketFd = 0;
    }

    fSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    Init(&fServAddr, portno, "", use_timeout);

    if (fSocketFd < 0)
    {
        fError.HandleError("ERROR opening socket", GLOCATION);
    }

    if (bind(fSocketFd, (struct sockaddr *)&fServAddr, sizeof(fServAddr)) < 0)
    {
        fError.HandleError("Error on binding", GLOCATION);
    }

    int newfSocketFd = 0;

    while (fDoRun == true)
    {
        listen(fSocketFd, 100);
        socklen_t clilen = sizeof(fReplAddr);
        newfSocketFd = accept(fSocketFd, (struct sockaddr *)&fReplAddr, &clilen);

        if (newfSocketFd < 0)
        {
            continue;
        }

        bzero(fBuffer, MAX_TCP_BUFFER_SIZE);

        int n = read(newfSocketFd, fBuffer, MAX_TCP_BUFFER_SIZE - 1);

        if (n < 0)
        {
            fError.HandleError("ERROR reading from socket", GLOCATION);
            continue;
        }

        string reply = HandleMessage(fBuffer, n);
        n = write(newfSocketFd, reply.c_str(), reply.size());
        if (n < 0)
        {
            fError.HandleError("ERROR writing to socket", GLOCATION);
        }
    } // end of endless loop

    close(newfSocketFd);
    close(fSocketFd);
    return 0;
}

#endif
