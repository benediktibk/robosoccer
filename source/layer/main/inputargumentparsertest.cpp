#include "layer/main/inputargumentparsertest.h"
#include "layer/main/inputargumentparser.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

void InputArgumentParserTest::constructor_twoInputs_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("blub");
	arguments.push_back("--setOwnTeamColor");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_teamColorSetToLila_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("lila");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_validArgumentTeamColorRed_isValid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT_EQUAL(TeamColorRed, parser.getOwnTeamColor());
}

void InputArgumentParserTest::constructor_validArgumentTeamColorBlue_isValid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("blue");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT_EQUAL(TeamColorBlue, parser.getOwnTeamColor());
}

void InputArgumentParserTest::constructor_fourInputs_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("haha");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());

}
