// -*- mode: c++ -*-
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/
#include "TestUDP.h"

#include <com/GClientUDP.h>
#include <com/GServerUDP.h>

#include <com/GClientTCP.h>
#include <com/GServerTCP.h>
#include <thread>
#include <chrono>

TestUDP::TestUDP()
{

}

TestUDP::~TestUDP()
{

}


/*
TEST_F(TestUDP, write_read)
{
    std::shared_ptr<GServerUDP> server = std::make_shared<GServerUDP>();
    std::shared_ptr<GClientUDP>  client = std::make_shared<GClientUDP>();
    std::thread th_server = std::thread( &GServerUDP::Open, server,  4468, true);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    client->Open( "localhost", 4468 );
   // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    client->Write("lorem ipsum");
    string reply = client->Read();
  //  std::this_thread::sleep_for(std::chrono::milliseconds(100));
    client->Write("lorem ipsum2"); 
    reply = client->Read();
    EXPECT_EQ( reply,  "lorem ipsum2" );
  //  std::this_thread::sleep_for(std::chrono::milliseconds(100));
    client->Write("lorem ipsum3"); 
    reply = client->Read();
    EXPECT_EQ( reply,  "lorem ipsum3" );
    
    server->Stop();
    client->Stop();
    
    if( th_server.joinable() == true )
    {
        th_server.join();
    }
    else
    {
        FORCE_DEBUG("server thread is not joinable");
    }
}
*/


/*
TEST_F(TestUDP, write_read_tcp)
{
    std::shared_ptr<GServerTCP> server = std::make_shared<GServerTCP>();
    std::thread th_server = std::thread( &GServerTCP::Open, server,  4470, true);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::shared_ptr<GClientTCP>  client = std::make_shared<GClientTCP>();
    client->Open( "localhost", 4470 );
    client->Write("lorem ipsum");
    string reply = client->Read();
    client->Close();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    client->Open( "localhost", 4470 );
    client->Write("lorem ipsum2"); 
    reply = client->Read();
    EXPECT_EQ( reply,  "lorem ipsum2" );
    client->Close();
 
    std::this_thread::sleep_for(std::chrono::milliseconds(100));     
    client->Open( "localhost", 4470 );
    client->Write("lorem ipsum3"); 
    reply = client->Read();
    EXPECT_EQ( reply,  "lorem ipsum3" );
    client->Close();
    server->Stop();
    client->Stop();
    
    
    if( th_server.joinable() == true )
    {
        th_server.join();
    }
    else
    {
        FORCE_DEBUG("server thread is not joinable");
    }


   // POP();
}
*/