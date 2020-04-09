
// -*- mode: c++ -*-

#include <logging/LLogApi.h>

using namespace LOGMASTER;

#include <com/GClientTCP.h>
#include <logging/LLogApi.h>
#include <exception/GException.h>
#include <utilities/GNumbers.h>

#include <stdlib.h>


int main( int argc,  const char **argv )
{
    G_ASSERT_EXCEPTION(argc == 4, "usage %s  <hostname> <port> <message>", argv[0 ]);
    FORCE_DEBUG("HELLO WORLD");
    GClientTCP  *t =  new GClientTCP();
    string host = string(argv[1] );
    const int port = g_numbers()->ToInteger<int>(argv[2]);
    string msg = string(argv[3]); 
    t->Open(host, port);
    t->Write(msg);
    t->Close();
    delete t;
    return 0;
}


