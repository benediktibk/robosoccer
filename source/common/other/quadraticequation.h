#ifndef ROBOSOCCER_COMMON_OTHER_QUADRATICEQUATION_H
#define ROBOSOCCER_COMMON_OTHER_QUADRATICEQUATION_H

#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
class Compare;

class QuadraticEquation
{
public:
	QuadraticEquation(double a, double b, double c);

	std::vector<double> getSolutions(const Compare &compare) const;

private:
	double m_a;
	double m_b;
	double m_c;
};
}
}
}

#endif


