#pragma once

#include <string>

#include "XMPP/Payload.h"

class VersionPayload : public Payload {
	public:
		VersionPayload() {}

		std::string getName() const {
			return "";
		}

		std::string getVersion() const {
			return "";
		}
};
