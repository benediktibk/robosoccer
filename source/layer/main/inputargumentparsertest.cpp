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
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("12");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_validArgumentTeamColorRedClientNr12_isValid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("12");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT_EQUAL(TeamColorRed, parser.getOwnTeamColor());
	CPPUNIT_ASSERT_EQUAL(12, parser.getOwnClientNumber());

}

void InputArgumentParserTest::constructor_validArgumentTeamColorBlueClientNr12_isValid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("blue");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("12");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT_EQUAL(TeamColorBlue, parser.getOwnTeamColor());
	CPPUNIT_ASSERT_EQUAL(12, parser.getOwnClientNumber());
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

void InputArgumentParserTest::constructor_fifthInputsNotANumber_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("haha");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_fifthInputsAWrongNumber_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("24");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_firstClientNumberAndSecondTeamColor_isValid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT_EQUAL(TeamColorRed, parser.getOwnTeamColor());
	CPPUNIT_ASSERT_EQUAL(14, parser.getOwnClientNumber());
}




