//
// Created by stephane bourque on 2022-12-13.
//

#include "RESTAPI_ue_handler.h"
#include "framework/utils.h"
#include "StorageService.h"
#include "ar_RESTObjects/RESTAPI_LOCObjects.h"

namespace Arilia {

    void RESTAPI_ue_handler::DoGet() {
        auto ue = GetBinding("ue","");
        if(!OpenWifi::Utils::NormalizeMac(ue)) {
            return BadRequest(OpenWifi::RESTAPI::Errors::InvalidSerialNumber);
        }
        LOCObjects::UEEntry UE;
        if(OpenWifi::StorageService()->UELocatorDB().GetRecord("ue",ue,UE)) {
            return OpenWifi::RESTAPIHandler::Object(UE);
        }
    }

} // Arilia