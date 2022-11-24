//
// Created by stephane bourque on 2022-11-24.
//

#include "RESTAPI_LOCObjects.h"
#include <framework/RESTAPI_utils.h>

using OpenWifi::RESTAPI_utils::field_to_json;
using OpenWifi::RESTAPI_utils::field_from_json;

namespace Arilia::LOCObjects {

    void UELocation::to_json(Poco::JSON::Object &Obj) const {
        field_to_json(Obj,"AP", AP);
        field_to_json(Obj,"system", system);
        field_to_json(Obj,"reported", reported);
    }

    bool UELocation::from_json(const Poco::JSON::Object::Ptr &Obj) {
        try {
            field_from_json(Obj,"AP", AP);
            field_from_json(Obj,"system", system);
            field_from_json(Obj,"reported", reported);
            return true;
        } catch (...) {
        }
        return false;
    }

    void UELocationEntry::to_json(Poco::JSON::Object &Obj) const {
        field_to_json(Obj,"MAC", MAC);
        field_to_json(Obj,"locations", locations);
        field_to_json(Obj,"created", created);
        field_to_json(Obj,"lastReport", lastReport);
    }

    bool UELocationEntry::from_json(const Poco::JSON::Object::Ptr &Obj) {
        try {
            field_from_json(Obj,"MAC", MAC);
            field_from_json(Obj,"locations", locations);
            field_from_json(Obj,"created", created);
            field_from_json(Obj,"lastReport", lastReport);
            return true;
        } catch (...) {
        }
        return false;
    }

} // Arilia
