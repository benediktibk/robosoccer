#include "layer/abstraction/storageimpl.h"
#include "layer/main/application.h"
#include "common/logging/loggerimpl.h"
#include "common/time/watchimpl.h"
#include "layer/main/inputargumentparser.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sstream>

using namespace std;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;

Application *application = 0;

void signalHandler(int signal)
{
	if (signal == 2 && application != 0)
		application->stop();
}

vector<string> getAllIpAdresses()
{
	vector<string> result;
	ifaddrs *allAddresses = 0;
	ifaddrs *currentAddress = 0;

	getifaddrs(&allAddresses);

	for (currentAddress = allAddresses; currentAddress != 0; currentAddress = currentAddress->ifa_next)
	{
		if (string(currentAddress->ifa_name) == "lo")
			continue;

		if (currentAddress ->ifa_addr->sa_family == AF_INET)
		{
			void *address = &((struct sockaddr_in *)currentAddress->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, address, addressBuffer, INET_ADDRSTRLEN);
			stringstream stream;
			stream << currentAddress->ifa_name << ":\t" << addressBuffer;
			result.push_back(stream.str());
		}
		else if (currentAddress->ifa_addr->sa_family == AF_INET6)
		{
			void *address = &((struct sockaddr_in6 *)currentAddress->ifa_addr)->sin6_addr;
			char addressBuffer[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, address, addressBuffer, INET6_ADDRSTRLEN);
			stringstream stream;
			stream << currentAddress->ifa_name << ":\t" << addressBuffer;
			result.push_back(stream.str());
		}
	}

	if (allAddresses != 0)
		freeifaddrs(allAddresses);

	return result;
}

int main(int argc, char **argv)
{
	struct sigaction sigIntHandler;
	vector<string> arguments = InputArgumentParser::convertArguments(argc, argv);

	InputArgumentParser parser(arguments);
	if (!parser.isValid())
	{
		cerr << "invalid arguments" << endl << endl;
		cout << parser.usage() << endl;
		return 1;
	}

	vector<string> ipAdresses = getAllIpAdresses();

	cout << "##### ---------------------------\n##### GAME START" << endl;
	cout << "##### own team color    : " << parser.getOwnTeamColor() << endl;
	cout << "##### client number     : " << parser.getOwnClientNumber() << endl;

	if (parser.disableHardwareCheck())
			cout << "##### Hardware Check Disabled   : " << "TRUE" << endl;
		else
			cout << "##### Hardware Check Disabled   : " << "FALSE" << endl;

	if (parser.disableRouteServer())
			cout << "##### Route Server Disabled   : " << "TRUE" << endl;
		else
			cout << "##### Route Server Disabled   : " << "FALSE" << endl;

	if (parser.routeServerPortSet())
			cout << "##### Route Server Port   : " << parser.getRouteServePort() << endl;
		else
			cout << "##### Route Server Port   : " << parser.getRouteServePort() << endl;

	cout << "##### Ip Adresses:" << endl;
	for (vector<string>::const_iterator i = ipAdresses.begin(); i != ipAdresses.end(); ++i)
		cout << "##### " << *i << endl;

	cout << "##### ---------------------------" << endl;

	application = new Application(parser.getOwnTeamColor(), parser.getOwnClientNumber(), !parser.disableHardwareCheck());

	sigIntHandler.sa_handler = signalHandler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
	sigaction(SIGPIPE, &sigIntHandler, NULL);

	application->run();
	delete application;
	application = 0;
	return 0;
}
