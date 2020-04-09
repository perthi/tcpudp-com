// -*- mode: c++ -*-

#ifndef GUPDSERVER_H
#define GUPDSERVER_H

#include "GComErrorHandler.h"
#include "GCom.h"
#include <string>

using std::string;


#include <utilities/GDefinitions.h>

class  GServerUDP : public GCom
{
public:
    API  GServerUDP();
    virtual API  ~GServerUDP();
    virtual int API  Open( const int portno, const bool use_timout = true ) override;
    
private:
    //GComErrorHandler fError;
};


#endif
