//
// Created by stephane bourque on 2022-12-13.
//

#pragma once
#include "framework/RESTAPI_Handler.h"

namespace Arilia {

    class RESTAPI_ap_handler : public OpenWifi::RESTAPIHandler{
    public:
        RESTAPI_ap_handler(const OpenWifi::RESTAPIHandler::BindingMap &bindings, Poco::Logger &L, OpenWifi::RESTAPI_GenericServerAccounting & Server, uint64_t TransactionId, bool Internal)
                : RESTAPIHandler(bindings, L,
                                 std::vector<std::string>{
                                         Poco::Net::HTTPRequest::HTTP_GET,
                                         Poco::Net::HTTPRequest::HTTP_OPTIONS},
                                 Server,
                                 TransactionId,
                                 Internal){}

        static auto PathName() { return std::list<std::string>{"/api/v1/ap/{serialNumber}"}; };
    private:
        void DoGet() final;
        void DoPost() final {};
        void DoPut() final {};
        void DoDelete() final {};
    };

} // Arilia