#include "common/other/console.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace RoboSoccer::Common::Other;

char Console::getAsynchronousInput()
{
	char key = -1;
	int input = 0;
	termios newTermIOSettings;
	termios oldTermIOSSettings;

	input = fileno(stdin);
	tcgetattr(input, &oldTermIOSSettings);
	newTermIOSettings = oldTermIOSSettings;
	newTermIOSettings.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(input, TCSANOW, &newTermIOSettings);
	key = getchar();
	tcsetattr(input, TCSANOW, &oldTermIOSSettings);
	return key;
}

Console::Console()
{ }

