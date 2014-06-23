#ifndef ROBOSOCCER_LAYER_ABSTRACTION_TCPSERVERSOCKETIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_TCPSERVERSOCKETIMPL_H

#include "layer/abstraction/tcpserversocket.h"
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Logging
{
	class Logger;
}
}
namespace Layer
{
namespace Abstraction
{
	class TCPServerSocketImpl :
			public TCPServerSocket
	{
	public:
		TCPServerSocketImpl(Common::Logging::Logger &logger, unsigned int port);
		virtual ~TCPServerSocketImpl();

		virtual void updateClients();
		virtual void sendString(std::string const &message);
		virtual bool isValid() const;

	private:
		void acceptNewClients();
		void removeDisconnectedClients();
		void log(std::string const &message);

	private:
		Common::Logging::Logger &m_logger;
		bool m_valid;
		int m_serverSocket;
		std::vector<int> m_clientSockets;
		std::vector<int> m_disconnectedClients;
	};
}
}
}

#endif