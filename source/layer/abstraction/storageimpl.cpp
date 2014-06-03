#include "layer/abstraction/storageimpl.h"
#include "layer/abstraction/ballimpl.h"
#include "layer/abstraction/refereeimpl.h"
#include "layer/abstraction/readablerobotimpl.h"
#include "layer/abstraction/controllablerobotimpl.h"
#include <kogmo_rtdb.hxx>
#include <assert.h>
#include <sstream>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;
using namespace std;

StorageImpl::StorageImpl(int clientNumber, TeamColor teamColor, Logger &logger, Watch const &watch) :
	m_dataBase(0),
	m_ball(0),
	m_referee(0)
{
	stringstream clientName;
	// the construction of the name string is basically copied from the sample code
	clientName << "pololu_client_" << static_cast<char>(clientNumber + '0');
	m_dataBase = new KogniMobil::RTDBConn(clientName.str().c_str(), 0.1, "");
	m_ball = new BallImpl(*m_dataBase);
	m_referee = new RefereeImpl(*m_dataBase, teamColor, logger);
	TeamColor enemyColor;
	if (teamColor == TeamColorBlue)
		enemyColor = TeamColorRed;
	else
		enemyColor = TeamColorBlue;
	m_enemyRobots.reserve(3);
	m_enemyRobots.push_back(new ReadableRobotImpl(0, *m_dataBase, enemyColor));
	m_enemyRobots.push_back(new ReadableRobotImpl(1, *m_dataBase, enemyColor));
	//m_enemyRobots.push_back(new ReadableRobotImpl(2, *m_dataBase, enemyColor));
	m_ownRobots.reserve(3);
	m_ownRobots.push_back(new ControllableRobotImpl(0, *m_dataBase, teamColor, watch, logger));
	m_ownRobots.push_back(new ControllableRobotImpl(1, *m_dataBase, teamColor, watch, logger));
	m_ownRobots.push_back(new ControllableRobotImpl(2, *m_dataBase, teamColor, watch, logger));
}

StorageImpl::~StorageImpl()
{
	delete m_ball;
	m_ball = 0;
	delete m_referee;
	m_referee = 0;

	for (vector<ReadableRobot*>::iterator i = m_enemyRobots.begin(); i != m_enemyRobots.end(); ++i)
		delete *i;
	m_enemyRobots.clear();
	for (vector<ControllableRobot*>::iterator i = m_ownRobots.begin(); i != m_ownRobots.end(); ++i)
		delete *i;
	m_ownRobots.clear();

	delete m_dataBase;
	m_dataBase = 0;
}

Ball const& StorageImpl::getBall() const
{
	return *m_ball;
}

ReadableRobot const& StorageImpl::getEnemyRobot(unsigned int number) const
{
	assert(number <= 2);
	return *(m_enemyRobots[number]);
}

ControllableRobot &StorageImpl::getOwnRobot(unsigned int number)
{
	assert(number <= 2);
	return *(m_ownRobots[number]);
}

RefereeBase &StorageImpl::getReferee()
{
	return *m_referee;
}

