#pragma once

class Session {
	public:
		enum EncryptionType { EncryptWhenAvailable, AlwaysEncrypt };

		Session() {
		}

		void setEncryptConnection(EncryptionType) {
		}

		void start() {
		}
		
		bool isConnected() {
			return true;
		}

		bool isEncrypted() {
			return true;
		}

		bool isNegotiatingTLS() {
			return true;
		}

		bool hasError() {
			return true;
		}
};
