
// -*- mode: c++ -*-

#include <logging/LLogApi.h>
#include <exception/GException.h>
#include <utilities/GNumbers.h>

using namespace LOGMASTER;

#include <com/GServerTCP.h>

#include <stdlib.h>


int main(int argc, const char **argv )
{
    G_ASSERT_EXCEPTION(argc == 2, "usage %s  <port>", argv[0 ]);
    
    
    const int port = g_numbers()->ToInteger<int>(argv[1]);
    
    
    
    FORCE_DEBUG("HELLO WORLD");
    
    GServerTCP *t =  new GServerTCP();

    t->Open(port);
    
    delete t;
    
    return 0;
}


