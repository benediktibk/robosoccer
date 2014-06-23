#include "layer/abstraction/tcpserversocketimpl.h"
#include "common/logging/logger.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sstream>
#include <string.h>
#include <assert.h>
#include <algorithm>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace std;

TCPServerSocketImpl::TCPServerSocketImpl(Logger &logger, unsigned int port) :
	m_logger(logger)
{
	sockaddr_in serverAddress;
	m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_serverSocket < 0)
	{
		m_valid = false;
		m_logger.logErrorToConsoleAndWriteToGlobalLogFile("could not open server socket");
		return;
	}
	else
		m_valid = true;

	if (port < 1024 || port > 49151)
	{
		m_valid = false;
		m_logger.logErrorToConsoleAndWriteToGlobalLogFile("invalid port number");
		return;
	}

	// set the struct to zero
	bzero((char *)&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	// accept connections on all addresses
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(port);

	int bindResult = bind(m_serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress));

	if (bindResult < 0)
	{
		m_valid = false;
		m_logger.logErrorToConsoleAndWriteToGlobalLogFile("could not bind the server socket");
		return;
	}

	listen(m_serverSocket, 10);
	fcntl(m_serverSocket, F_SETFL, O_NONBLOCK);
}

TCPServerSocketImpl::~TCPServerSocketImpl()
{
	for (vector<int>::const_iterator i = m_clientSockets.begin(); i != m_clientSockets.end(); ++i)
		close(*i);
	m_clientSockets.clear();
	close(m_serverSocket);
	m_serverSocket = -1;
}

void TCPServerSocketImpl::updateClients()
{
	removeDisconnectedClients();
	acceptNewClients();
}

void TCPServerSocketImpl::sendString(const string &message)
{
	const char *dataPointer = message.c_str();

	for (vector<int>::const_iterator i = m_clientSockets.begin(); i != m_clientSockets.end(); ++i)
	{
		int clientSocket = *i;
		size_t writtenBytes = write(clientSocket, dataPointer, message.size());
		if (writtenBytes != message.size() && count(m_disconnectedClients.begin(), m_disconnectedClients.end(), clientSocket) == 0)
			m_disconnectedClients.push_back(clientSocket);
	}
}

bool TCPServerSocketImpl::isValid() const
{
	return m_valid;
}

void TCPServerSocketImpl::acceptNewClients()
{
	sockaddr_in clientAddress;
	int clientSocket;
	int size = sizeof(clientAddress);

	do
	{
		clientSocket = accept(
					m_serverSocket,
					reinterpret_cast<sockaddr*>(&clientAddress),
					reinterpret_cast<socklen_t*>(&size));

		if (clientSocket >= 0)
		{
			m_clientSockets.push_back(clientSocket);
			log("new client connected");
		}
	} while(clientSocket >= 0);
}

void TCPServerSocketImpl::removeDisconnectedClients()
{
	for (vector<int>::const_iterator i = m_disconnectedClients.begin(); i != m_disconnectedClients.end(); ++i)
	{
		int client = *i;
		vector<int>::iterator clientIterator = find(m_clientSockets.begin(), m_clientSockets.end(), client);
		if (clientIterator != m_clientSockets.end())
		{
			m_clientSockets.erase(clientIterator);
			log("lost connection to client");
			close(client);
		}
	}

	m_disconnectedClients.clear();
}

void TCPServerSocketImpl::log(const string &message)
{
	m_logger.logToLogFileOfType(Logger::LogFileTypeRouteInformationServer, message);
}
