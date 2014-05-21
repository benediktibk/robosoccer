#ifndef ROBOSOCCER_LAYER_CONTROL_USERINPUTFETCHER_H
#define ROBOSOCCER_LAYER_CONTROL_USERINPUTFETCHER_H

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class UserInputFetcher
	{
	public:
		virtual ~UserInputFetcher() { }

		virtual bool selectionMade() const = 0;
		virtual bool playOffensive() const = 0;
		virtual void update() = 0;
	};
}
}
}

#endif


