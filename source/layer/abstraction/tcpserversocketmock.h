#ifndef ROBOSOCCER_LAYER_ABSTRACTION_TCPSERVERSOCKETMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_TCPSERVERSOCKETMOCK_H

#include "layer/abstraction/tcpserversocket.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class TCPServerSocketMock :
			public TCPServerSocket
	{
	public:
		virtual void updateClients();
		virtual void sendString(std::string const &message);
		virtual bool isValid() const;
	};
}
}
}

#endif