#pragma once

#include <boost/signal.hpp>

#include "XMPP/StringList.h"
#include "XMPP/MockIQChannel.h"

class RoomDiscoverer {
	public:
		RoomDiscoverer(MockIQChannel*) {}

		void discoverRooms() {
		}

		StringList getDiscoveredRooms() const {
			return StringList();
		}

		bool isFinished() {
			return true;
		}

		boost::signal<void (StringList)> onFinished;
};
