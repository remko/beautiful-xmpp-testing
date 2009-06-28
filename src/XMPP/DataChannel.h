#pragma once

#include <string>
#include <boost/signal.hpp>

using namespace std;

class DataChannel {
	public:
		virtual void sendData(const string& data) = 0; 
		boost::signal<void (const string&)> onDataReceived; /* (*) The signal <literal>onDataReceived</literal> has one <literal>string</literal> parameter (and no return value). When the signal is emitted, the <literal>string</literal> argument containing the data received will be passed to the connected slot method. */
};
