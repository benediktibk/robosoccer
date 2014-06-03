#include "layer/control/treenoderesultgetbehindball.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/robot.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Control;

TreeNodeResultGetBehindBall::TreeNodeResultGetBehindBall(
		RoboSoccer::Common::Logging::Logger &logger, RoboSoccer::Layer::Abstraction::RefereeBase &referee,
		RoboSoccer::Layer::Autonomous::Team &ownTeam, const RoboSoccer::Layer::Autonomous::EnemyTeam &enemyTeam,
		const RoboSoccer::Layer::Autonomous::IntelligentBall &ball, const RoboSoccer::Layer::Autonomous::TargetPositionFetcher &targetPositionFetcher) :
	TreeNodeResult(logger, referee, ownTeam, enemyTeam, ball, targetPositionFetcher)
{

}

void TreeNodeResultGetBehindBall::execute()
{
	//! @todo use useful targets
	//! @todo consider ignoreBall and driveSlowlyAtTheEnd
	m_ownTeam.getFirstFieldPlayer().goTo(Pose(Point(-0.5,-0.5), Angle()), false, false);
	m_ownTeam.getSecondFieldPlayer().goTo(Pose(Point(-0.5,0.5), Angle()), false, false);
}
