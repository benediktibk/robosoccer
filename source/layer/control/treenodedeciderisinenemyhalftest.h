#ifndef ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISINENEMYHALFTEST_H
#define ROBOSOCCER_LAYER_CONTROL_TREENODEDECIDERISINENEMYHALFTEST_H

#include "layer/control/treenodedecidertest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Control
{
class TreeNodeDeciderIsInEnemyHalfTest :
		public TreeNodeDeciderTest
	{
		CPPUNIT_TEST_SUITE(TreeNodeDeciderIsInEnemyHalfTest);
		CPPUNIT_TEST(getChild_ballInOwnZone_defend);
		CPPUNIT_TEST(getChild_ballInEnemyZone_attack);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual TreeNodeDecider* createTestNode();

	private:
		void getChild_ballInOwnZone_defend();
		void getChild_ballInEnemyZone_attack();


	};
}
}
}

#endif


