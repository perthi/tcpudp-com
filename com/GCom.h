// -*- mode: c++ -*-
#pragma once

#include "GComErrorHandler.h"
#define MAX_TCP_BUFFER_SIZE 4096

#include <sys/types.h>

#include <netinet/in.h>
#include <utilities/GDefinitions.h>

#define TIMOUT_SEC 1        // This is effectively the amount of s/us to wait for a complete packet,
#define TEMOUT_US  200000   // currently at 0.2s delay.
// #define UDP_REPLY_PORT 45502
// #define TCP_REPLY_PORT 45501
#define MAXLINE 1024

#include <thread>
#include <chrono>


enum class eCOM_MODE
{
  TCP,
  UDP,
  UNKNOWN
};


class  GCom
{
public:
    API GCom();
    virtual API ~GCom();
    inline void Start() { fDoRun = true; };
  //  virtual inline void Stop() { fDoRun = false; };
    virtual int API  Open(   const string hostname,  const int portno, const bool use_timout = true  );
    virtual int API  Open(   const int portno,  const bool use_timout = true  );
    virtual int Close();
    virtual string API  HandleMessage(const char * const buffer, const size_t length ) ;
    virtual string API  HandleMessage(const string msg) ;
  //  virtual  int OpenClient( const string hostname, const int portno,  const __socket_type type );
    virtual int Write( const string msg );
    virtual string Read(  );
    virtual  void Stop();
    static  string  Enum2String( const  eCOM_MODE mode );

protected:

  ///  void Reset();
    virtual int Init( sockaddr_in *addr, const int portno, const string hostname = "",  bool set_timeout = true );

    virtual int OpenSocket( const __socket_type type);

    int Bind( const bool connect = true );

    GComErrorHandler fError;
    int fSocketFd = 0;  /*!< socket file descriptor */
    int fSocketReply = 0;  /*!< socket file descriptor */
    char fBuffer[ MAX_TCP_BUFFER_SIZE ];

    #ifndef _WIN32
	sockaddr_in fServAddr;
    sockaddr_in fReplAddr;
    #endif


    bool fDoRun = true;



    // string fHostname = "";

};

