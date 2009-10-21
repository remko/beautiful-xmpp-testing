#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "Swiften/Client/Client.h"
#include "Swiften/Network/Timer.h"
#include "Swiften/EventLoop/MainEventLoop.h"
#include "Swiften/EventLoop/SimpleEventLoop.h"
#include "Swiften/Queries/Requests/GetRosterRequest.h"

using namespace Swift;
using namespace boost;

SimpleEventLoop eventLoop;

typedef Client XMPPClient;
void handleConnected();
void handleRosterResponse(shared_ptr<RosterPayload>, optional<Error> error);

/// TestClient

XMPPClient* xmppClient = NULL;
bool rosterReceived = false;

int main(int argc, char* argv[]) {
	xmppClient = new XMPPClient(JID(getenv("TEST_JID")), getenv("TEST_PASS"));
	xmppClient->onConnected.connect(&handleConnected); /* (*) When connected (and authenticated), call <literal>handleConnected</literal>. */
	xmppClient->connect();
	return rosterReceived;
}

void handleConnected() {
	GetRosterRequest* rosterRequest = new GetRosterRequest(xmppClient);
	rosterRequest->onResponse.connect(bind(&handleRosterResponse, _1, _2)); /* (*) When a response for the roster request is received, call <literal>handleRosterReceived</literal> with the response and status as arguments. */
	rosterRequest->send();
}

void handleRosterResponse(shared_ptr<RosterPayload>, optional<Error> error) {
	rosterReceived = !error; /* (*) If there was no error, we received the roster properly. */
	xmppClient->disconnect();
}

