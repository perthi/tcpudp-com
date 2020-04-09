// -*- mode: c++ -*-
#ifndef GComErrorHandler_H
#define GComErrorHandler_H
/**************************************************************************
 * This file is property of and copyright by Flekkefjord Elektro  2017   *
 *                                                                        *
 * Author: Per Thomas Hille <pth@embc.no> for the UHCW project.*
 * Contributors are mentioned in the code where appropriate.              *
 * Please report bugs to pth@embc.no                                *
 **************************************************************************/


#include <utilities/GDefinitions.h>
#include <utilities/GLocation.h>

class  GComErrorHandler
{
public:
    API  GComErrorHandler();
    virtual API  ~GComErrorHandler();
    void API HandleError(const char *msg, const GLocation l );
};

#endif
