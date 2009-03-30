#pragma once

#include <boost/signal.hpp>
#include <vector>

#include "XMPP/XMLElement.h"

class MockXMLElementChannel {
	public:
		MockXMLElementChannel() {
		}

		virtual void sendXMLElement(const XMLElement& element) {
			sentXMLElements.push_back(element);
		}

		boost::signal<void (const XMLElement&)> onXMLElementReceived;
		std::vector<XMLElement> sentXMLElements;
};
