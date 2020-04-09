// -*- mode: c++ -*-

#include "GCom.h"
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <exception/GException.h>
#include <logging/LLogApi.h>
#include <thread>
#include <chrono>

#include <sstream>

using namespace LOGMASTER;


GCom::GCom() :  fError(),
     fSocketFd(0),
     fSocketReply(0),
     fServAddr(),
     fReplAddr(),
     fDoRun(true)
{

}


GCom::~GCom()
{

}

// void
// GCom::Reset()
// {
//     memset(&fServAddr, 0, sizeof( fServAddr));
//     memset(&fReplAddr, 0, sizeof( fReplAddr));
// }


int
GCom::Init( sockaddr_in *addr, const int portno, const string hostname, bool set_timeout  )
{
    memset( addr, 0, sizeof( sockaddr_in ) );

  ///  Reset();
    addr->sin_family = AF_INET;
    addr->sin_port = htons(portno);
    addr->sin_addr.s_addr = INADDR_ANY;

    if(hostname !="")
    {
      struct hostent *server = gethostbyname(hostname.c_str());

      if( server == nullptr )
      {
        fError.HandleError( ("no such host " + hostname).c_str(), GLOCATION );
        return -1;
      }
      else
      {
        bcopy((char *)server->h_addr,
                (char *)&fServAddr.sin_addr.s_addr,
                    server->h_length);
      }
    }

    // Set timeout if server does not respond
    if(set_timeout == true )
    {
        struct timeval tv;
        tv.tv_sec = TIMOUT_SEC;
        tv.tv_usec = TEMOUT_US;
        setsockopt(  fSocketFd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    }

    int enable = 1;

    if (setsockopt( fSocketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        fError.HandleError("setsockopt(SO_REUSEADDR) failed", GLOCATION );
        ///return -1;
    }
    return 0;
}


int
GCom::OpenSocket( const __socket_type type)
{
  if(fSocketFd != 0)
    {
      Close();
    }

    fSocketFd = socket(AF_INET, type, 0);

    if ( fSocketFd  < 0)
    {
      fError.HandleError("ERROR opening socket", GLOCATION);
      return -1;
    }
    else
    {
        return 0;
    }
}


int
GCom::Bind( const bool do_connect )
{
  if (bind(fSocketFd, (struct sockaddr *) &fReplAddr, sizeof(fReplAddr)) < 0)
    {
      fError.HandleError("bind failed", GLOCATION );
      return -1;
    }

    if( do_connect == true )
    {
      if (connect(  fSocketFd,(struct sockaddr *) &fServAddr,sizeof(fServAddr)) < 0)
      {
        fError.HandleError("ERROR connecting", GLOCATION);
        return -1;
      }
    }

    return 0;

}


int
GCom::Close()
{
    int ret = close( fSocketFd );
    fSocketFd = 0;
    return ret;
}



int
GCom::Write(  const string msg )
{
  // int n;
  //   n = write( fSocketFd, msg.c_str() , msg.size() );

  //   if (n < 0)
  //   {
  //     fError.HandleError("ERROR writing to socket", GLOCATION);
  //     return -1;
  //   }

  //   return n;


    COM_DEBUG("msg size = %d", msg.size() );
    int n = 0;
     n = sendto(  fSocketFd  , msg.c_str(),
     msg.size(), MSG_CONFIRM, (const struct sockaddr *) &fServAddr, sizeof(fServAddr) );
    COM_DEBUG("sendt %d bytes", n );

    if (n < 0)
    {
      fError.HandleError("ERROR writing to socket", GLOCATION);
      return -1;
    }

    return n;
}

string
GCom::Read()
{
  int n = -1;
  socklen_t len = 0;
  memset(fBuffer,0, sizeof(fBuffer));

//  n = recvfrom( fSocketFd, (char *)fBuffer, MAXLINE,
 //               MSG_WAITALL, (struct sockaddr *) &fServAddr,
  //              &len);

    n = recvfrom( fSocketFd, (char *)fBuffer, MAXLINE,
                  MSG_DONTWAIT, (struct sockaddr *) &fServAddr,
                  &len);

  if(n < 0)
  {
    COM_FATAL( "errno = %d, n = %d, len = %d: %s, fSocketFd = %d", errno, n, len, fBuffer, fSocketFd );
    fError.HandleError("recvfrom failed", GLOCATION );
    return "read failed !!";
  }


  COM_INFO( "Server n = %d, len = %d: %s", n, len, fBuffer );
  string tmp;

  for(int i=0; i < n; i ++ )
  {
    tmp.push_back(fBuffer[i]);
  }

  HandleMessage(tmp);

  return  tmp;
}

int
GCom::Open(   const string /*hostname*/,  const int /*portno*/, const bool /*use_timout*/ )
{
    COM_FATAL("This function must be overidden");
    return -1;
}


int
GCom::Open(   const int /*portno*/,  const bool /*use_timout*/  )
{
    COM_FATAL("This function must be overidden");
    return -1;
}

void
GCom::Stop()
{
    fDoRun = false;
    Close();
}


// int
// GCom::OpenClient(  const string hostname,  const int portno, const __socket_type type  )
// {
//    /// return  OpenClient( hostname, portno, SOCK_DGRAM );

//     if( OpenSocket(type ) < 0 )
//     {
//       return -1;
//     }

//     Init( &fReplAddr,portno );
//     std::this_thread::sleep_for(std::chrono::milliseconds(2));
//     Init( &fServAddr, portno, hostname );

//     if (bind(fSocketFd, (struct sockaddr *) &fReplAddr, sizeof(fReplAddr)) < 0)
//     {
//       fError.HandleError("ERROR setting reply port", GLOCATION );
//       return -1;
//     }
//     if (connect(  fSocketFd,(struct sockaddr *) &fServAddr,sizeof(fServAddr)) < 0)
//     {
//       fError.HandleError("ERROR connecting", GLOCATION);
//       return -1;
//     }

//     return 0;
// }


string
GCom::HandleMessage(const char * const buffer, const size_t length )
{
  string tmp = "";
  for( size_t i = 0; i < length; i ++ )
  {
     tmp.push_back( buffer[ i]);
  }

  return HandleMessage(tmp);

}


string
GCom::HandleMessage(const string msg)
{
   /// G_ERROR("This function must be overriden, msg = %s", msg.c_str() );
    return msg;
}



string
GCom::Enum2String( const  eCOM_MODE mode )
{
  switch (mode)
  {
  case  eCOM_MODE::TCP:
    return "TCP";
    break;
  case  eCOM_MODE::UDP:
    return "UDP";
    break;
 case  eCOM_MODE::UNKNOWN:
    return "UNKOWN";
    break;
  default:
      std::stringstream buffer;
      buffer << "ERROR, mode (" << (int)mode << ") not reckognized";
      return buffer.str();
    break;
  }

}