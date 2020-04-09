
// -*- mode: c++ -*-

#include <logging/LLogApi.h>

using namespace LOGMASTER;

#include <com/GServerTCP.h>
#include <com/GClientTCP.h>

#include <thread>
#include <chrono>

void client();
void sever();

int main()
{
    FORCE_DEBUG("HELLO WORLD");
    
    GServerTCP *t =  new GServerTCP();
    
     std::thread th_server( sever );
    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) ); 
    std::thread th_client( client );

   

    th_client.join();
    th_server.join();


    delete t;
    
    return 0;
}


void sever()
{ 
    FORCE_DEBUG("running server");
    GServerTCP *t =  new GServerTCP();
    t->Open(4444);
}


void client()
{
    FORCE_DEBUG("running client");
    GClientTCP *t =  new GClientTCP();
    t->Open("localhost", 4444);
    FORCE_DEBUG("sending first message");
    t->Write("lorem ipsum");
    FORCE_DEBUG("done....");  
    t->Read();
    std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) ); 
    FORCE_DEBUG("sending second message");
    t->Write("Dolores sit amet");
    t->Read();
    FORCE_DEBUG("done....");
}