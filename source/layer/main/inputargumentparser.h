#ifndef ROBOSOCCER_LAYER_MAIN_INPUTARGUMENTPARSER_H
#define ROBOSOCCER_LAYER_MAIN_INPUTARGUMENTPARSER_H

#include "layer/abstraction/teamcolor.h"
#include <vector>
#include <string>
#include <list>

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
	class InputArgumentParser
	{
	public:
		InputArgumentParser(std::vector<std::string> const &arguments);

		bool isValid() const;
		Layer::Abstraction::TeamColor getOwnTeamColor() const;
		int getOwnClientNumber() const;
		bool disableHardwareCheck() const;
		std::string usage() const;
		unsigned int getRouteServePort() const;
		bool routeServerPortSet() const;
		bool disableRouteServer() const;
		bool disableLogging() const;

		static std::vector<std::string> convertArguments(int argc, char **argv);

	private:
		void parseTeamColor(std::list<std::string> &arguments);
		void parseClientNumber(std::list<std::string> &arguments);
		void parseDisableHardwareCheck();
		void parseDisableRouteServer();
		void parseRouteServerPort(std::list<std::string> &arguments);
		void parseDisableLogging();

	private:
		int m_ownClientNumber;
		Layer::Abstraction::TeamColor m_ownTeamColor;
		bool m_disableHardwareCheck;
		bool m_disableRouteServer;
		bool m_valid;
		unsigned int m_routeServerPort;
		bool m_routeServerPortSet;
		bool m_disableLogging;
	};
}
}
}

#endif
