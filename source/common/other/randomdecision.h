#ifndef ROBOSOCCER_COMMON_OTHER_RANDOMDECISION_H
#define ROBOSOCCER_COMMON_OTHER_RANDOMDECISION_H

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
class RandomDecision
{
public:
	RandomDecision(double possibilityForTrue);

	bool decide() const;

private:
	double m_possibilityForTrue;
};
}
}
}

#endif
