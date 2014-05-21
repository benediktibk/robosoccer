#ifndef ROBOSOCCER_LAYER_CONTROL_USERINPUTFETCHERMOCK_H
#define ROBOSOCCER_LAYER_CONTROL_USERINPUTFETCHERMOCK_H

#include "layer/control/userinputfetcher.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
	class UserInputFetcherMock :
			public UserInputFetcher
	{
	public:
		UserInputFetcherMock();

		virtual bool selectionMade() const;
		virtual bool playOffensive() const;
		virtual void update();

		void setSelectionMade(bool value);
		void setPlayOffensive(bool value);
		unsigned int getCallsToUpdate() const;

	private:
		bool m_selectionMade;
		bool m_playOffensive;
		unsigned int m_callsToUpdate;
	};
}
}
}

#endif


