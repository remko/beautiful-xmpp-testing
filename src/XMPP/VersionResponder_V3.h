#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <string>

#include "XMPP/IQ.h"
#include "XMPP/MockIQChannel.h"

class VersionResponder_V3 {
	public:
		VersionResponder_V3(MockIQChannel* xmlElementChannel) : xmlElementChannel(xmlElementChannel) {
			xmlElementChannel->onIQReceived.connect(bind(&VersionResponder_V3::handleIncomingIQ, this, _1));
		}
	
		void setVersion(const std::string&, const std::string& = "") {
		}

		void handleIncomingIQ(const IQ& element) {
			//xmlElementChannel->sendIQ(
		}
	
		MockIQChannel* xmlElementChannel;
};
