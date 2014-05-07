#include "layer/control/userinputfetcherimpl.h"
#include "common/other/console.h"
#include <assert.h>
#include <iostream>

using namespace std;
using namespace RoboSoccer::Layer::Control;
using namespace RoboSoccer::Common::Other;

UserInputFetcherImpl::UserInputFetcherImpl() :
	m_selectionMade(false)
{
	printOutMessage();
}

bool UserInputFetcherImpl::selectionMade() const
{
	return m_selectionMade;
}

bool UserInputFetcherImpl::playOffensive() const
{
	assert(m_selectionMade);
	return m_playOffensive;
}

void UserInputFetcherImpl::update()
{
	char key = Console::getAsynchronousInput();

	if (key == 'o')
	{
		m_selectionMade = true;
		m_playOffensive = true;
	}
	else if (key == 'd')
	{
		m_selectionMade = true;
		m_playOffensive = false;
	}
	else if (key != 0)
		printOutMessage();
}

void UserInputFetcherImpl::printOutMessage() const
{
	cout << endl << "press 'o' for offensive or 'd' for defensive mode: ";
}