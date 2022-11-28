//
// Created by stephane bourque on 2022-11-21.
//

#pragma once

#include "framework/orm.h"
#include "ar_RESTObjects/RESTAPI_LOCObjects.h"

namespace Arilia {

typedef Poco::Tuple<
	std::string,    //  MAC
	std::string,    //  Locations
	uint64_t,       //  created = 0;
	uint64_t        //  lastreport = 0;
	> UELocatorRecordTuple;
	typedef std::vector <UELocatorRecordTuple> UELocatorRecordTupleList;

	class UELocatorDB : public ORM::DB<UELocatorRecordTuple, Arilia::LOCObjects::UELocationEntry> {
	  public:
        UELocatorDB( const std::string &name, const std::string &shortname, OpenWifi::DBType T, Poco::Data::SessionPool & P, Poco::Logger &L);
		virtual ~UELocatorDB() {}
		inline uint32_t Version() override {
			return 1;
		}

		bool Upgrade(uint32_t from, uint32_t &to) override;
		void Initialize();
        bool UpdateUE(const std::string &UE, const LOCObjects::UELocation &L);
        bool RemoveOldUEs(std::uint64_t MaximumDays);
	};

}