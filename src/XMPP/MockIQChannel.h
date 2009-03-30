#pragma once

#include <boost/signal.hpp>
#include <vector>

#include "XMPP/IQ.h"

class MockIQChannel {
	public:
		MockIQChannel() {
		}

		virtual void sendIQ(const IQ& iq) {
			sentIQs.push_back(iq);
			onSendIQ(iq);
		}

		boost::signal<void (const IQ&)> onIQReceived;
		boost::signal<void (const IQ&)> onSendIQ;
		std::vector<IQ> sentIQs;
};
