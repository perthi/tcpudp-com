// -*- mode: c++ -*-
#ifndef GClientTCP_H
#define GClientTCP_H


#include "GComErrorHandler.h"
#include "GCom.h"
#include <string>
using std::string;

#include <utilities/GDefinitions.h>

class  GClientTCP : public GCom
{
public:
    API  GClientTCP();
	virtual API  ~GClientTCP();
    virtual int  API  Open(   const string hostname,  const int portno,  const bool use_timout = true ) override;
   /// void Stop();

   /// virtual void  API  Close();
   // virtual int  API Write( const string msg ) ;
  //  virtual string API  Read( ) ;

private:
   // GComErrorHandler fError;
  ///  int fSocketFd = 0;  /*!< socket file descriptor */

};




#endif
