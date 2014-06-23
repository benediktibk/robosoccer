#ifndef ROBOSOCCER_LAYER_ABSTRACTION_TCPSERVERSOCKET_H
#define ROBOSOCCER_LAYER_ABSTRACTION_TCPSERVERSOCKET_H

#include <string>

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class TCPServerSocket
	{
	public:
		virtual ~TCPServerSocket() { }

		virtual void updateClients() = 0;
		virtual void sendString(std::string const &message) = 0;
		virtual bool isValid() const = 0;
	};
}
}
}

#endif