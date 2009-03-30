#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "XMPP/VersionResponder_V1.h"
#include "XMPP/MockDataChannel.h"
#include "CppUnitAliases.h"

class VersionResponderTest_V1 : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(VersionResponderTest_V1);
		CPPUNIT_TEST(testHandleIncomingRequest);
		CPPUNIT_TEST_SUITE_END();

	public:
		void testHandleIncomingRequest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(VersionResponderTest_V1);

/// Tests

void VersionResponderTest_V1::testHandleIncomingRequest() {
	// Set up the test fixture
	MockDataChannel dataChannel;
	VersionResponder_V1 responder(&dataChannel);
	responder.setVersion("Swift", "1.0");

	// Fake incoming request data on the data channel
	dataChannel.onDataReceived(
		"<iq type='get' from='alice@wonderland.lit/RabbitHole' id='version-1'>"
			"<query xmlns='jabber:iq:version'/>"
		"</iq>");

	// Verify the outcome
	ASSERT_EQUAL(
		"<iq type='result' to='alice@wonderland.lit/RabbitHole' id='version-1'>"
			"<query xmlns='jabber:iq:version'>"
				"<name>Swift</name>"
				"<version>1.0</version>"
			"</query>"
		"</iq>", 
		dataChannel.sentData);
}
