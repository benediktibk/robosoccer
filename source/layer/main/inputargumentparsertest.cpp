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
	CPPUNIT_ASSERT(!parser.disableHardwareCheck());
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
	CPPUNIT_ASSERT(!parser.disableHardwareCheck());
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
	CPPUNIT_ASSERT(!parser.disableHardwareCheck());
}

void InputArgumentParserTest::constructor_disableHardwareCheckSet_disableHardwareCheck()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--disableHardwareCheck");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT_EQUAL(TeamColorRed, parser.getOwnTeamColor());
	CPPUNIT_ASSERT_EQUAL(14, parser.getOwnClientNumber());
	CPPUNIT_ASSERT(parser.disableHardwareCheck());
}

void InputArgumentParserTest::constructor_clientNumberTwice_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_teamColorTwice_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_disableHardwareCheckTwice_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--disableHardwareCheck");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--disableHardwareCheck");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_teamColorMissing_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_clientNumberMissing_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_disableRouteServerSet_disableHardwareCheck()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--disableHardwareCheck");
	arguments.push_back("--disableRouteServer");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT_EQUAL(TeamColorRed, parser.getOwnTeamColor());
	CPPUNIT_ASSERT_EQUAL(14, parser.getOwnClientNumber());
	CPPUNIT_ASSERT(parser.disableHardwareCheck());
	CPPUNIT_ASSERT(parser.disableRouteServer());
}

void InputArgumentParserTest::constructor_disableRouteServerTwice_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--disableHardwareCheck");
	arguments.push_back("--disableRouteServer");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--disableRouteServer");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_setRouteServerPort_isValid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--routeServerPort");
	arguments.push_back("1234");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT_EQUAL(TeamColorRed, parser.getOwnTeamColor());
	CPPUNIT_ASSERT_EQUAL(14, parser.getOwnClientNumber());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1234, parser.getRouteServePort());
	CPPUNIT_ASSERT(!parser.disableRouteServer());
	CPPUNIT_ASSERT(!parser.disableHardwareCheck());
}

void InputArgumentParserTest::constructor_setRouteServerPortAndNoNumer_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--routeServerPort");
	arguments.push_back("drei");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_setRouteServerPortAndNumberOutOfRange_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--routeServerPort");
	arguments.push_back("123456");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_disableRouteServerAndPortSet_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--routeServerPort");
	arguments.push_back("123456");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--disableRouteServer");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}

void InputArgumentParserTest::constructor_disableLoggingSet_disableLogging()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--disableLogging");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(parser.disableLogging());
}

void InputArgumentParserTest::constructor_disableLoggingNotSet_enableLogging()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(parser.isValid());
	CPPUNIT_ASSERT(!parser.disableLogging());
}

void InputArgumentParserTest::constructor_disableLoggingTwiceSet_isInvalid()
{
	vector<string> arguments;
	arguments.push_back("bla");
	arguments.push_back("--setOwnClientNumber");
	arguments.push_back("14");
	arguments.push_back("--setOwnTeamColor");
	arguments.push_back("red");
	arguments.push_back("--disableLogging");
	arguments.push_back("--disableLogging");

	InputArgumentParser parser(arguments);

	CPPUNIT_ASSERT(!parser.isValid());
}
