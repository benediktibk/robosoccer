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

	cout << "##### ---------------------------\n##### GAME START" << endl;
	cout << "##### own team color    : " << parser.getOwnTeamColor() << endl;
	cout << "##### client number     : " << parser.getOwnClientNumber() << endl;

	if (parser.disableHardwareCheck())
			cout << "##### Hardware Check Disabled   : " << "TRUE" << endl;
		else
			cout << "##### Hardware Check Disabled   : " << "FALSE" << endl;

	if (true)
			cout << "##### Route Server Port   : " << "!!add correct port" << endl;
		else
			cout << "##### Route Server Port   : " << "port" << endl;

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
