#pragma once

#include <string>

#include "XMPP/Payload.h"

class DiscoInfo : public Payload {
	public:
		DiscoInfo(const std::string& = "") {}
};
