#include "layer/abstraction/tcpserversocketmock.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

void TCPServerSocketMock::updateClients()
{ }

void TCPServerSocketMock::sendString(const string &)
{ }

bool TCPServerSocketMock::isValid() const
{
	return true;
}
