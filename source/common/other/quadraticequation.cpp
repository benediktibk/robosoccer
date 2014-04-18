#include "common/other/quadraticequation.h"
#include "common/geometry/compare.h"
#include <assert.h>
#include <math.h>

using namespace std;
using namespace RoboSoccer::Common::Other;

QuadraticEquation::QuadraticEquation(double a, double b, double c) :
	m_a(a),
	m_b(b),
	m_c(c)
{
	assert(m_a != 0);
}

vector<double> QuadraticEquation::getSolutions(const Compare &compare) const
{
	vector<double> solutions;
	double discriminant = m_b*m_b-4*m_a*m_c;

	if (compare.isFuzzyEqual(0, discriminant))
	{
		double onlySolution = (-1)*m_b/(2*m_a);
		solutions.push_back(onlySolution);
		return solutions;
	}
	else if (discriminant < 0)
		return solutions;
	else
	{
		double squareRoot = sqrt(discriminant);
		double firstSolution = ((-1)*m_b + squareRoot)/(2*m_a);
		double secondSolution = ((-1)*m_b - squareRoot)/(2*m_a);
		solutions.push_back(firstSolution);
		solutions.push_back(secondSolution);
		return solutions;
	}
}
