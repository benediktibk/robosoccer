#ifndef ROBOSOCCER_LAYER_CONTROL_USERINPUTFETCHERIMPL_H
#define ROBOSOCCER_LAYER_CONTROL_USERINPUTFETCHERIMPL_H

#include "layer/control/userinputfetcher.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class UserInputFetcherImpl :
			public UserInputFetcher
	{
	public:
		UserInputFetcherImpl();

		virtual bool selectionMade() const;
		virtual bool playOffensive() const;
		virtual void update();

	private:
		void printOutMessage() const;

	private:
		bool m_selectionMade;
		bool m_playOffensive;
	};
}
}
}

#endif


