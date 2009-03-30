#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "XMPP/VersionResponder_V2.h"
#include "XMPP/MockXMLElementChannel.h"
#include "CppUnitAliases.h"

class VersionResponderTest_V2 : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(VersionResponderTest_V2);
		CPPUNIT_TEST(testHandleIncomingRequest);
		CPPUNIT_TEST_SUITE_END();

	public:
		void testHandleIncomingRequest();
};

CPPUNIT_TEST_SUITE_REGISTRATION(VersionResponderTest_V2);

/// Tests

void VersionResponderTest_V2::testHandleIncomingRequest() {
	// Set up the test fixture
	MockXMLElementChannel xmlElementChannel;
	VersionResponder_V2 responder(&xmlElementChannel);
	responder.setVersion("Swift", "1.0"); 

	// Fake incoming request stanza on the stanza channel
	xmlElementChannel.onXMLElementReceived(XMLElement::fromString(
		"<iq type='get' from='alice@wonderland.lit/RabbitHole' id='version-1'>"
			"<query xmlns='jabber:iq:version'/>"
		"</iq>"));

	// Verify the outcome
	ASSERT_EQUAL(1, xmlElementChannel.sentXMLElements.size());
	XMLElement response = xmlElementChannel.sentXMLElements[0];
	ASSERT_EQUAL("iq", response.getTagName());
	ASSERT_EQUAL("result", response.getAttribute("type"));
	ASSERT_EQUAL("id", response.getAttribute("version-1"));
	ASSERT_EQUAL("alice@wonderland.lit/RabbitHole", response.getAttribute("to"));
	XMLElement queryElement = response.getElementByTagNameNS(
		"query", "jabber:iq:version");
	ASSERT(queryElement.isValid());
	XMLElement nameElement = queryElement.getElementByTagName("name");
	ASSERT(nameElement.isValid());
	ASSERT_EQUAL("Swift", nameElement.getText());
	XMLElement versionElement = queryElement.getElementByTagName("version");
	ASSERT(versionElement.isValid());
	ASSERT_EQUAL("1.0", versionElement.getText());
}
