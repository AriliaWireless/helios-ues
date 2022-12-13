//
// Created by stephane bourque on 2022-11-24.
//

#include "RESTAPI_LOCObjects.h"
#include <framework/RESTAPI_utils.h>

using OpenWifi::RESTAPI_utils::field_to_json;
using OpenWifi::RESTAPI_utils::field_from_json;

namespace Arilia::LOCObjects {

    void UELocation::to_json(Poco::JSON::Object &Obj) const {
        field_to_json(Obj,"ap", ap);
        field_to_json(Obj,"system", system);
        field_to_json(Obj,"reported", reported);
        field_to_json(Obj,"bssid", bssid);
        field_to_json(Obj,"ssid", ssid);
    }

    bool UELocation::from_json(const Poco::JSON::Object::Ptr &Obj) {
        try {
            field_from_json(Obj,"ap", ap);
            field_from_json(Obj,"system", system);
            field_from_json(Obj,"reported", reported);
            field_from_json(Obj,"bssid", bssid);
            field_from_json(Obj,"ssid", ssid);
            return true;
        } catch (...) {
        }
        return false;
    }

    void UEEntry::to_json(Poco::JSON::Object &Obj) const {
        field_to_json(Obj,"ue", ue);
        field_to_json(Obj,"locations", locations);
        field_to_json(Obj,"created", created);
        field_to_json(Obj,"lastReport", lastReport);
    }

    bool UEEntry::from_json(const Poco::JSON::Object::Ptr &Obj) {
        try {
            field_from_json(Obj,"ue", ue);
            field_from_json(Obj,"locations", locations);
            field_from_json(Obj,"created", created);
            field_from_json(Obj,"lastReport", lastReport);
            return true;
        } catch (...) {
        }
        return false;
    }

    void APLocation::to_json(Poco::JSON::Object &Obj) const {
        field_to_json(Obj,"system", system);
        field_to_json(Obj,"reported", reported);
    }

    bool APLocation::from_json(const Poco::JSON::Object::Ptr &Obj) {
        try {
            field_from_json(Obj,"system", system);
            field_from_json(Obj,"reported", reported);
            return true;
        } catch (...) {
        }
        return false;

    }

    void APClients::to_json(Poco::JSON::Object &Obj) const {
        field_to_json(Obj,"ap", ap);
        field_to_json(Obj,"location", location);
        field_to_json(Obj,"clients", clients);
    }

    bool APClients::from_json(const Poco::JSON::Object::Ptr &Obj) {
        try {
            field_from_json(Obj,"ap", ap);
            field_from_json(Obj,"location", location);
            field_from_json(Obj,"clients", clients);
            return true;
        } catch (...) {
        }
        return false;

    }

} // Arilia
