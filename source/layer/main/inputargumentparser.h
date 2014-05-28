#ifndef ROBOSOCCER_LAYER_MAIN_INPUTARGUMENTPARSER_H
#define ROBOSOCCER_LAYER_MAIN_INPUTARGUMENTPARSER_H

#include "layer/abstraction/teamcolor.h"
#include <vector>
#include <string>

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

			static std::vector<std::string> convertArguments(int argc, char **argv);

		private:
			Layer::Abstraction::TeamColor m_ownTeamColor;
			bool m_valid;
	};
}
}
}

#endif
