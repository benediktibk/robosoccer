#include "common/states/statemachinetest.h"
#include "common/states/statemachine.h"
#include "common/states/statemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;
using namespace std;

void StateMachineTest::update_empty_stateGotAtLeastOneCallToNextState()
{
	LoggerMock logger;
	StateMock *state = new StateMock(logger);
	StateMachine stateMachine(state);

	stateMachine.update();

	CPPUNIT_ASSERT(state->getCallsToNextState() > 0);
}

void StateMachineTest::update_noStateChange_stateGotAtLeastOneCallToUpdate()
{
	LoggerMock logger;
	StateMock *state = new StateMock(logger);
	StateMachine stateMachine(state);

	stateMachine.update();

	CPPUNIT_ASSERT(state->getCallsToUpdate() > 0);
}

void StateMachineTest::update_stateChange_currentStateIsNewOne()
{
	LoggerMock logger;
	StateMock *oldState = new StateMock(logger);
	StateMock *newState = new StateMock(logger);
	oldState->setNextState(newState);
	StateMachine stateMachine(oldState);

	stateMachine.update();

	CPPUNIT_ASSERT(newState == &(stateMachine.getCurrentState()));
}

void StateMachineTest::update_stateChange_currentStateGotAtLeastOneCallToUpdate()
{
	LoggerMock logger;
	StateMock *oldState = new StateMock(logger);
	StateMock *newState = new StateMock(logger);
	oldState->setNextState(newState);
	StateMachine stateMachine(oldState);

	stateMachine.update();

	CPPUNIT_ASSERT(newState->getCallsToUpdate() > 0);
}

void StateMachineTest::getNameOfCurrentState_stateMock_StateMock()
{
	LoggerMock logger;
	StateMock *state = new StateMock(logger);
	StateMachine stateMachine(state);

	CPPUNIT_ASSERT_EQUAL(string("StateMock"), stateMachine.getNameOfCurrentState());
}
