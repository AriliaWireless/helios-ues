//
// Created by stephane bourque on 2022-11-24.
//

#pragma once

#include <string>

#include <Poco/JSON/Object.h>

namespace Arilia::LOCObjects {

    struct UELocation {
        std::string         AP;
        std::string         system;
        std::uint64_t       reported=0;

        void to_json(Poco::JSON::Object &Obj) const;
        bool from_json(const Poco::JSON::Object::Ptr &Obj);
    };

    struct UELocationEntry {
        std::string             MAC;
        std::vector<UELocation> locations;
        std::uint64_t           created=0;
        std::uint64_t           lastReport=0;

        void to_json(Poco::JSON::Object &Obj) const;
        bool from_json(const Poco::JSON::Object::Ptr &Obj);
    };

} // Arilia

