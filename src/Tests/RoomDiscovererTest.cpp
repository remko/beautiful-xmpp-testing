#include <map>
#include <string>
#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "CppUnitAliases.h"
#include "XMPP/RoomDiscoverer.h"
#include "XMPP/DiscoInfo.h"
#include "XMPP/DiscoItems.h"
#include "XMPP/MockIQChannel.h"

using namespace boost;
using namespace std;

class RoomDiscovererTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(RoomDiscovererTest);
		CPPUNIT_TEST(testDiscoverRooms);
		CPPUNIT_TEST_SUITE_END();
	
	public:
		void setUp();
		void tearDown();

		void testDiscoverRooms();
	
	private:
		void respondToIQ(const IQ&);

		MockIQChannel* channel;

		typedef map<string, DiscoInfo> InfoResponseMap;
		InfoResponseMap infoResponses;

		typedef map<string, DiscoItems> ItemsResponseMap;
		ItemsResponseMap itemsResponses;
};

CPPUNIT_TEST_SUITE_REGISTRATION(RoomDiscovererTest);

/// Fixture Definition

void RoomDiscovererTest::setUp() {
	channel = new MockIQChannel();
	channel->onSendIQ.connect(bind(&RoomDiscovererTest::respondToIQ, this, _1)); /* (*) Whenever an IQ is sent, pass it to <literal>respondToIQ</literal>, which will respond to it. */
}

void RoomDiscovererTest::tearDown() {
	delete channel;
}

void RoomDiscovererTest::respondToIQ(const IQ& iq) {
	ASSERT(iq.getType() == IQ::Get);
	if (iq.getPayload<DiscoItems>()) { 
		ItemsResponseMap::const_iterator response = itemsResponses.find(iq.getTo());
		ASSERT(response != itemsResponses.end());
		channel->onIQReceived(iq.createResponse(new DiscoItems(response->second)));
	}
	else if (iq.getPayload<DiscoInfo>()) {
		InfoResponseMap::const_iterator response = infoResponses.find(iq.getTo());
		ASSERT(response != infoResponses.end());
		channel->onIQReceived(iq.createResponse(new DiscoInfo(response->second)));
	}
	else {
		FAIL("Unexpected IQ");
	}
}

/// Tests
void RoomDiscovererTest::testDiscoverRooms() {
	// Set up the responses
	itemsResponses["wonderland.lit"] = /* (*) Specify the response to a <literal>disco#items</literal> request for the top-level <literal>wonderland.lit</literal> domain. In this case, two items are returned: <literal>pubsub</literal> and <literal>rooms</literal>. */
		DiscoItems("pubsub.wonderland.lit", "rooms.wonderland.lit");
	infoResponses["pubsub.wonderland.lit"] = /* (*) Specify the response to a <literal>disco#info</literal> request for the <literal>pubsub</literal> service. In this case, respond with the namespace of the PubSub protocol. */
		DiscoInfo("http://jabber.org/protocol/pubsub");
	itemsResponses["pubsub.wonderland.lit"] = /* (*) Specify the items belonging to the <literal>pubsub</literal> service. These are added to test whether <literal>RoomDiscoverer</literal> doesn’t pick up items from non-MUC services. */
		DiscoItems("blogs@pubsub.wonderland.lit", "croquet@pubsub.wonderland.lit"); 
	infoResponses["rooms.wonderland.lit"] = /* (*) Respond that the <literal>rooms</literal> service supports MUC. */
		DiscoInfo("http://jabber.org/protocol/muc");
	itemsResponses["rooms.wonderland.lit"] = /* (*) Specify the list of items (i.e., rooms) of the MUC service. */
		DiscoItems("teaparty@rooms.wonderland.lit", "croquet@rooms.wonderland.lit");

	// Set up room discoverer
	RoomDiscoverer discoverer(channel);

	// Execute room discovery
	discoverer.discoverRooms();

	// Test results
	ASSERT(discoverer.isFinished());
	StringList rooms = discoverer.getDiscoveredRooms();
	ASSERT_EQUAL(2, rooms.size());
	ASSERT(rooms.contains("teaparty@rooms.wonderland.lit"));
	ASSERT(rooms.contains("croquet@rooms.wonderland.lit"));
}
