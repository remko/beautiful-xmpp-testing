#pragma once

class Payload;

class IQ {
	public:
		enum Type { Get };

		IQ(Type, Payload*) {
		}

		Type getType() const {
			return Get;
		}

		template<typename T> const T* getPayload() const {
			return 0;
		}

		std::string getTo() const {
			return "";
		}

		IQ createResponse(Payload* payload) const {
			return IQ(Get, payload);
		}
};
