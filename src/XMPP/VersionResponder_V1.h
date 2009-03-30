#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <string>

#include "XMPP/DataChannel.h"

class VersionResponder_V1 {
	public:
		VersionResponder_V1(DataChannel* dataChannel) : dataChannel(dataChannel) {
			dataChannel->onDataReceived.connect(bind(&VersionResponder_V1::handleIncomingData, this, _1));
		}
	
		void setVersion(const std::string&, const std::string&) {
		}

		void handleIncomingData(const std::string&) {
			dataChannel->sendData("<iq type='result' to='alice@wonderland.lit/RabbitHole' id='version-1'>"
				"<query xmlns='jabber:iq:version'>"
					"<name>Swift</name>"
					"<version>1.0</version>"
				"</query>"
			"</iq>");
		}
	
		DataChannel* dataChannel;
};
