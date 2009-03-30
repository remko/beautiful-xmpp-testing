#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <string>

#include "XMPP/XMLElement.h"
#include "XMPP/MockXMLElementChannel.h"

class VersionResponder_V2 {
	public:
		VersionResponder_V2(MockXMLElementChannel* xmlElementChannel) : xmlElementChannel(xmlElementChannel) {
			xmlElementChannel->onXMLElementReceived.connect(bind(&VersionResponder_V2::handleIncomingXMLElement, this, _1));
		}
	
		void setVersion(const std::string&, const std::string&) {
		}

		void handleIncomingXMLElement(const XMLElement& element) {
			//xmlElementChannel->sendXMLElement(
		}
	
		MockXMLElementChannel* xmlElementChannel;
};
