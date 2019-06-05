#include "MulticastClient.h"
#include "MulticastServer.h"

#include <thread>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int c;
	std::thread clientThread;
	bool createClient = false;
	bool createServer = false;
	std::string networkInterface;

	while ((c = getopt (argc, argv, "sci:")) != -1)
	{
		switch (c)
		{
			case 's':
			{
				createServer = true;
			}
			break;

			case 'c':
			{
				createClient = true;
			}
			break;

			case 'i':
			{
				networkInterface = std::string(optarg);
			}
			break;

			case '?':
			{
				if (optopt == 'i')
				{
					fprintf (stderr, "Option -%i requires the interface name.\n", optopt);
				}
				else if (isprint (optopt))
				{
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				}
				else
				{
				  fprintf (stderr,
						   "Unknown option character `\\x%x'.\n",
						   optopt);
				}
			}
			break;
		}
	}

	if (createClient)
	{
		printf("Creating a client \n");
		clientThread = std::thread { MulticastClient::CreateClient, networkInterface };
		//give some time for the client to run
		sleep(1);
	}

	if (createServer)
	{
		printf("Creating a server \n");
		MulticastServer::CreateServer(networkInterface);
	}

	if (clientThread.joinable())
	{
		clientThread.join();
	}

}
