//
// Created by stephane bourque on 2022-11-24.
//

#pragma once

#include <string>

#include <Poco/JSON/Object.h>

namespace Arilia::LOCObjects {

    struct UELocation {
        std::string         ap;
        std::string         system;
        std::uint64_t       reported=0;
        std::string         bssid;
        std::string         ssid;

        void to_json(Poco::JSON::Object &Obj) const;
        bool from_json(const Poco::JSON::Object::Ptr &Obj);
    };

    struct UEEntry {
        std::string             ue;
        std::vector<UELocation> locations;
        std::uint64_t           created=0;
        std::uint64_t           lastReport=0;

        void to_json(Poco::JSON::Object &Obj) const;
        bool from_json(const Poco::JSON::Object::Ptr &Obj);
    };

    struct APLocation {
        std::string         system;
        std::uint64_t       reported=0;

        void to_json(Poco::JSON::Object &Obj) const;
        bool from_json(const Poco::JSON::Object::Ptr &Obj);
    };

    struct APClients {
        std::string             ap;
        APLocation              location;
        std::vector<UEEntry>    clients;

        void to_json(Poco::JSON::Object &Obj) const;
        bool from_json(const Poco::JSON::Object::Ptr &Obj);
    };

} // Arilia

