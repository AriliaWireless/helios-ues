//
// Created by stephane bourque on 2022-04-28.
//

#pragma once

#include "framework/UI_WebSocketClientServer.h"

namespace OpenWifi {
	class UELocatorWebSocketClient : public UI_WebSocketClientProcessor {
	  public:
		explicit UELocatorWebSocketClient(Poco::Logger &Logger);
		virtual ~UELocatorWebSocketClient();
		virtual void Processor(const Poco::JSON::Object::Ptr &O, std::string &Answer, bool &Done, const SecurityObjects::UserInfo &UserInfo );
		void ws_command_serial_number_search( const Poco::JSON::Object::Ptr &O, bool &Done, std::string &Answer);
		void ws_command_exit( const Poco::JSON::Object::Ptr &O, bool &Done, std::string &Answer);
		void ws_command_invalid( const Poco::JSON::Object::Ptr &O, bool &Done, std::string &Answer);

	  private:
		Poco::Logger & Logger_;
		inline Poco::Logger & Logger() { return Logger_; }
	};
}
