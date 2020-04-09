// -*- mode: c++ -*-
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/
#include "GComErrorHandler.h"

#include <stdio.h>
///#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <logging/LLogApi.h>

using namespace LOGMASTER;

GComErrorHandler::GComErrorHandler()
{
    
    
}


GComErrorHandler::~GComErrorHandler()
{

    
}


#ifdef _WIN32
void
GComErrorHandler::HandleError(const char*  msg,  const GLocation l  )
{
    COM_FATAL( "Not implemented for Windoes" );
}
#else 
void
GComErrorHandler::HandleError(const char * msg,   const GLocation l  )
{
    // COM_FATAL("%s: %s", msg,  strerror(errno) );
    // LLogging::Instance()->Log(  eMSGLEVEL::LOG_FATAL, eMSGSYSTEM::SYS_COM, l,  "errno = %s,  errno = %s", msg, strerror(errno) );
    COM_FATAL("[%s]FATAL ERROR: %s", l.c_str(), msg);
}
#endif