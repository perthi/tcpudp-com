// -*- mode: c++ -*-

#ifndef GServerTCP_H
#define GServerTCP_H

#include "GComErrorHandler.h"
#include "GCom.h"

#include <string>
using std::string;


#include <utilities/GDefinitions.h>

class  GServerTCP : public GCom
{
public:
    API  GServerTCP();
    virtual API  ~GServerTCP();
    virtual int API  Open( const int portno, const bool use_timout = true) override;
    
private:
    //GComErrorHandler fError;
};


#endif
