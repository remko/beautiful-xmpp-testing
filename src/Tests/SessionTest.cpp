#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "CppUnitAliases.h"

#include "XMPP/Session.h"

class SessionTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(SessionTest);
		CPPUNIT_TEST(testStart_Encrypt);
		CPPUNIT_TEST(testStart_ForceEncyptWithoutServerSupport);
		CPPUNIT_TEST(testStart_FailingConnection);
		CPPUNIT_TEST_SUITE_END();

	public:
		void testStart_Encrypt();
		void testStart_ForceEncyptWithoutServerSupport();
		void testStart_FailingConnection();

	private:
		Session* createSession(const std::string&) {
			return 0;
		}

		void sessionOpensConnection() {}
		void sessionSendsStreamStart() {}
		void sessionSendsStartTLS() {}
		void serverAcceptsConnection() {}
		void serverSendsStreamStart() {}
		void serverSendsStreamFeaturesWithStartTLS() {}
		void serverSendsStreamFeaturesWithoutStartTLS() {}
		void serverSendsTLSProceed() {}
		void closeConnection() {}
		void completeTLSHandshake() {}
};

CPPUNIT_TEST_SUITE_REGISTRATION(SessionTest);

/// TestEncrypt

void SessionTest::testStart_Encrypt() {
	Session* session = createSession("alice@wonderland.lit/RabbitHole");
	session->setEncryptConnection(Session::EncryptWhenAvailable);
	session->start();

	sessionOpensConnection();
	serverAcceptsConnection();
	sessionSendsStreamStart(); /* (*) Before sending XML elements over the stream, the client initializes the stream by sending an opening <literal>&lt;stream&gt;</literal> tag. All subsequent elements are children of this element. When the connection is closed, the closing <literal>&lt;/stream&gt;</literal> tag is sent. */
	serverSendsStreamStart(); /* (*) Similarly to the client, the server also starts the stream by sending a <literal>&lt;stream&gt;</literal> tag. */
	serverSendsStreamFeaturesWithStartTLS(); /* (*) Immediately after sending the opening stream tag, the server sends a list of all the features it supports. In this case, it announces support for stream encryption using <firstterm>StartTLS</firstterm>. */
	sessionSendsStartTLS(); /* (*) The client sends a <literal>&lt;starttls/&gt;</literal> element to request the server to encrypt the connection. */
	serverSendsTLSProceed(); /* (*) The server responds with a <literal>&lt;proceed/&gt;</literal>, indicating that the TLS negotiation (or <emphasis>handshake</emphasis>) can start. */
	
	ASSERT(session->isNegotiatingTLS());

	completeTLSHandshake(); /* (*) Fake a successful TLS handshake. */
	sessionSendsStreamStart(); /* (*) Immediately after the handshake, the 
		stream is reset, and the stream header is resent in an encrypted form. */
	serverSendsStreamStart();

	ASSERT(session->isConnected());
	ASSERT(session->isEncrypted());
}

/// TestEncryptWithoutServerSupport
void SessionTest::testStart_ForceEncyptWithoutServerSupport() {
	Session* session = createSession("alice@wonderland.lit/RabbitHole");
	session->setEncryptConnection(Session::AlwaysEncrypt);
	session->start();

	sessionOpensConnection();
	serverAcceptsConnection();
	sessionSendsStreamStart();
	serverSendsStreamStart();
	serverSendsStreamFeaturesWithoutStartTLS();
	
	ASSERT(session->hasError());
}

/// TestFailingConnection
void SessionTest::testStart_FailingConnection() {
	Session* session = createSession("alice@wonderland.lit/RabbitHole");
	session->start();

	sessionOpensConnection();
	serverAcceptsConnection();
	sessionSendsStreamStart();
	serverSendsStreamStart();
	closeConnection();
	
	ASSERT(session->hasError());
}
