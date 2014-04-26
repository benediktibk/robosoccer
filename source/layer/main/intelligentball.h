#ifndef ROBOSOCCER_LAYER_MAIN_INTELLIGENTBALL_H
#define ROBOSOCCER_LAYER_MAIN_INTELLIGENTBALL_H

class Ball;

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
	class IntelligentBall
	{
	public:
		IntelligentBall();
	private:
		Ball *m_ball;
	};
}
}
}
#endif
