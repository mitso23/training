#include "MulticastClient.h"
#include "MulticastServer.h"

#include <thread>

int main(int argc, char* argv[])
{
    std::thread t { MulticastClient::CreateClient};
    //give some time for the client to run
    sleep(1);

    //start the server
    MulticastServer::CreateServer();
    t.join();
}
