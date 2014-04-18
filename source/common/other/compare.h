#ifndef ROBOSOCCER_COMMON_OTHER_COMPARE_H
#define ROBOSOCCER_COMMON_OTHER_COMPARE_H

#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
	class Compare
	{
	public:
		Compare(double epsilon);

		bool isFuzzyEqual(double value1, double value2) const;
		bool isFuzzyEqual(const std::vector<double> &one, const std::vector<double> &two) const;
		bool isFuzzyGreater(double value1, double value2) const;
		bool isFuzzySmaller(double value1, double value2) const;
		bool isStrictFuzzyGreater(double value1, double value2) const;
		bool isStrictFuzzySmaller(double value1, double value2) const;

	private:
		 double m_epsilon;
	};
}
}
}

#endif
