#ifndef ROBOSOCCER_LAYER_MAIN_INPUTARGUMENTPARSERTEST_H
#define ROBOSOCCER_LAYER_MAIN_INPUTARGUMENTPARSERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
	class InputArgumentParserTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(InputArgumentParserTest);
		CPPUNIT_TEST(constructor_twoInputs_isInvalid);
		CPPUNIT_TEST(constructor_teamColorSetToLila_isInvalid);
		CPPUNIT_TEST(constructor_validArgumentTeamColorRedClientNr12_isValid);
		CPPUNIT_TEST(constructor_validArgumentTeamColorBlueClientNr12_isValid);
		CPPUNIT_TEST(constructor_fourInputs_isInvalid);
		CPPUNIT_TEST(constructor_fifthInputsNotANumber_isInvalid);
		CPPUNIT_TEST(constructor_fifthInputsAWrongNumber_isInvalid);
		CPPUNIT_TEST(constructor_firstClientNumberAndSecondTeamColor_isValid);
		CPPUNIT_TEST(constructor_disableHardwareCheckSet_disableHardwareCheck);
		CPPUNIT_TEST(constructor_clientNumberTwice_isInvalid);
		CPPUNIT_TEST(constructor_teamColorTwice_isInvalid);
		CPPUNIT_TEST(constructor_disableHardwareCheckTwice_isInvalid);
		CPPUNIT_TEST(constructor_teamColorMissing_isInvalid);
		CPPUNIT_TEST(constructor_clientNumberMissing_isInvalid);
		CPPUNIT_TEST(constructor_disableServerPortSet_disableHardwareCheck);
		CPPUNIT_TEST(constructor_disableServerPortTwice_isInvalid);
		CPPUNIT_TEST(constructor_setRouteServerPort_isValid);
		CPPUNIT_TEST(constructor_setRouteServerPortAndNoNumer_isInvalid);
		CPPUNIT_TEST(constructor_setRouteServerPortAndNumberOutOfRange_isInvalid);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_twoInputs_isInvalid();
		void constructor_teamColorSetToLila_isInvalid();
		void constructor_validArgumentTeamColorRedClientNr12_isValid();
		void constructor_validArgumentTeamColorBlueClientNr12_isValid();
		void constructor_fourInputs_isInvalid();
		void constructor_fifthInputsNotANumber_isInvalid();
		void constructor_fifthInputsAWrongNumber_isInvalid();
		void constructor_firstClientNumberAndSecondTeamColor_isValid();
		void constructor_disableHardwareCheckSet_disableHardwareCheck();
		void constructor_clientNumberTwice_isInvalid();
		void constructor_teamColorTwice_isInvalid();
		void constructor_disableHardwareCheckTwice_isInvalid();
		void constructor_teamColorMissing_isInvalid();
		void constructor_clientNumberMissing_isInvalid();
		void constructor_disableServerPortSet_disableHardwareCheck();
		void constructor_disableServerPortTwice_isInvalid();
		void constructor_setRouteServerPort_isValid();
		void constructor_setRouteServerPortAndNoNumer_isInvalid();
		void constructor_setRouteServerPortAndNumberOutOfRange_isInvalid();
	};
}
}
}
#endif


