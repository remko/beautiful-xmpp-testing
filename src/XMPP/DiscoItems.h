#pragma once

#include "XMPP/Payload.h"

class DiscoItems : public Payload {
	public:
		DiscoItems(const std::string& = "", const std::string& = "") {}
};
