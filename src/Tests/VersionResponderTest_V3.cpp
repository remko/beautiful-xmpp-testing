#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "XMPP/VersionResponder_V3.h"
#include "XMPP/MockIQChannel.h"
#include "XMPP/VersionPayload.h"
#include "CppUnitAliases.h"

class VersionResponderTest_V3 : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(VersionResponderTest_V3);
		CPPUNIT_TEST(testHandleIncomingRequest);
		CPPUNIT_TEST_SUITE_END();

	public:
		void testHandleIncomingRequest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(VersionResponderTest_V3);

/// Tests

void VersionResponderTest_V3::testHandleIncomingRequest() {
	// Set up the test fixture
	MockIQChannel iqChannel;
	VersionResponder_V3 responder(&iqChannel);
	responder.setVersion("Swift"); 

	// Fake incoming request stanza on the stanza channel
	iqChannel.onIQReceived(IQ(IQ::Get, new VersionPayload()));

	// Verify the outcome
	ASSERT_EQUAL(1, iqChannel.sentIQs.size());
	const VersionPayload* payload = 
		iqChannel.sentIQs[0].getPayload<VersionPayload>();
	ASSERT(payload);
	ASSERT_EQUAL("Swift", payload->getName());
	ASSERT_EQUAL("Unknown version", payload->getVersion());
}
