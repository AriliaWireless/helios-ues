//
// Created by stephane bourque on 2021-10-23.
//

#include "framework/RESTAPI_SystemCommand.h"
#include "framework/RESTAPI_WebSocketServer.h"
#include "framework/RESTAPI_SystemConfiguration.h"

namespace OpenWifi {

    Poco::Net::HTTPRequestHandler * RESTAPI_ExtRouter(const std::string &Path, RESTAPIHandler::BindingMap &Bindings,
                                                            Poco::Logger & L, RESTAPI_GenericServerAccounting & S, uint64_t TransactionId) {

    	return RESTAPI_Router<
				RESTAPI_system_command,
				RESTAPI_system_configuration,
				RESTAPI_webSocketServer
				>(Path,Bindings,L, S, TransactionId);
    }

    Poco::Net::HTTPRequestHandler * RESTAPI_IntRouter(const std::string &Path, RESTAPIHandler::BindingMap &Bindings,
                                                            Poco::Logger & L, RESTAPI_GenericServerAccounting & S, uint64_t TransactionId) {

    	return RESTAPI_Router_I<
                RESTAPI_system_command,
                RESTAPI_system_configuration,
                RESTAPI_webSocketServer
                >(Path,Bindings,L, S, TransactionId);
	}
}