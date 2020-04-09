// -*- mode: c++ -*-
#ifndef GClientUDP_H
#define GClientUDP_H


#include "GComErrorHandler.h"
#include "GCom.h"

#include <string>

using std::string;

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


#include <utilities/GDefinitions.h>


class  GClientUDP : public GCom
{
public:
    API  GClientUDP();
    virtual API  ~GClientUDP();
    virtual int API  Open(   const string hostname,  const int portno, const bool use_timout = true  ) override;
  ///  int API Close();
//   virtual  int API  Write( const string msg ) ;
 //  virtual string API  Read()  ;

private:
   // GComErrorHandler fError;
 ///   int fSocketFd = 0;  /*!< socket file descriptor */

};

#endif
