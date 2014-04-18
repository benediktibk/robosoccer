#include "common/other/compare.h"
#include <math.h>

using namespace RoboSoccer::Common::Other;
using namespace std;

Compare::Compare(double epsilon) :
	m_epsilon(epsilon)
{ }

bool Compare::isFuzzyEqual(double value1, double value2) const
{
	return fabs(value1 - value2) < m_epsilon;
}

bool Compare::isFuzzyEqual(const vector<double> &one, const vector<double> &two) const
{
	if (one.size() != two.size())
		return false;

	for (size_t i = 0; i < one.size(); ++i)
		if (!isFuzzyEqual(one[i], two[i]))
			return false;

	return true;
}

bool Compare::isFuzzyGreater(double value1, double value2) const
{
	return value1 + m_epsilon > value2;
}

bool Compare::isFuzzySmaller(double value1, double value2) const
{
	return value1 < m_epsilon + value2;
}

bool Compare::isStrictFuzzyGreater(double value1, double value2) const
{
	return value1 > m_epsilon + value2;
}

bool Compare::isStrictFuzzySmaller(double value1, double value2) const
{
	return value1 + m_epsilon < value2;
}
