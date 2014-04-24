#include "layer/abstraction/refereeimpl.h"
#include <referee.h>
#include <assert.h>

using namespace RoboSoccer::Layer::Abstraction;

RefereeImpl::RefereeImpl(KogniMobil::RTDBConn &dataBase, TeamColor ownColor) :
	m_referee(new Referee(dataBase)),
	m_ownColor(ownColor)
{
	m_referee->Init();
}

RefereeImpl::~RefereeImpl()
{
	delete m_referee;
	m_referee = 0;
}

FieldSide RefereeImpl::getOwnFieldSide() const
{
	eSide blueSide = m_referee->GetBlueSide();

	if (blueSide == LEFT_SIDE)
	{
		switch(m_ownColor)
		{
		case TeamColorBlue:
			return FieldSideLeft;
		case TeamColorRed:
			return FieldSideRight;
		}
	}
	else if (blueSide == RIGHT_SIDE)
	{
		switch(m_ownColor)
		{
		case TeamColorBlue:
			return FieldSideRight;
		case TeamColorRed:
			return FieldSideLeft;
		}
	}

	return FieldSideInvalid;
}
