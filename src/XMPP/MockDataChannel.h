#pragma once

#include "XMPP/DataChannel.h"

class MockDataChannel : public DataChannel {
	public:
		MockDataChannel() {
		}

		virtual void sendData(const string& data) {
			sentData.append(data);
		}

		std::string sentData;
};
