#include "common/other/pidcontroller.h"
#include "common/time/stopwatch.h"
#include <algorithm>

using namespace RoboSoccer::Common::Other;
using namespace std;

PIDController::PIDController(double Kp, double Ki, double Kd, const Time::Watch &watch) :
	m_Kp(Kp),
	m_Ki(Ki),
	m_Kd(Kd),
	m_stopWatch(new Time::StopWatch(watch))
{
	resetTo(0);
}

PIDController::~PIDController()
{
	delete m_stopWatch;
	m_stopWatch = 0;
}

double PIDController::evaluate(double input)
{
	double time = max(m_stopWatch->getTimeAndRestart(), 0.01);
	m_integratorState += input*time;
	double result = m_Kp*input + m_Kd*(input - m_lastInput)/time + m_Ki*m_integratorState;
	m_lastInput = input;
	return result;
}

void PIDController::resetTo(double value)
{
	m_integratorState = 0;
	m_lastInput = value;
	m_stopWatch->getTimeAndRestart();
}
