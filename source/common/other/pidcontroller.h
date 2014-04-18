#ifndef ROBOSOCCER_COMMON_OTHER_PIDCONTROLLER_H
#define ROBOSOCCER_COMMON_OTHER_PIDCONTROLLER_H

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
	class StopWatch;
}
namespace Other
{
	class PIDController
	{
	public:
		PIDController(double Kp, double Ki, double Kd, const Time::Watch &watch);
		~PIDController();

		double evaluate(double input);
		void resetTo(double value);

	private:
		const double m_Kp;
		const double m_Ki;
		const double m_Kd;
		double m_integratorState;
		double m_lastInput;
		Time::StopWatch *m_stopWatch;
	};
}
}
}

#endif


