//
// Created by stephane bourque on 2022-11-21.
//

#include "storage_uelocator.h"

#include "framework/RESTAPI_utils.h"
#include "fmt/format.h"

namespace Arilia {
	static ORM::FieldVec UELocatorDB_Fields{
		ORM::Field{"MAC", 16, true},
		ORM::Field{"locations", ORM::FieldType::FT_TEXT},
		ORM::Field{"created", ORM::FieldType::FT_BIGINT},
		ORM::Field{"lastReport", ORM::FieldType::FT_BIGINT},
	};

	static ORM::IndexVec MakeIndices([[
    maybe_unused]] const std::string & shortname) {
		return ORM::IndexVec{
		};
	};

    UELocatorDB::UELocatorDB( const std::string &TableName, const std::string &Shortname ,OpenWifi::DBType T,
					   Poco::Data::SessionPool &P, Poco::Logger &L) :
		  DB(T, TableName.c_str(), UELocatorDB_Fields, MakeIndices(Shortname), P, L, Shortname.c_str()) {
	}

	bool UELocatorDB::Upgrade([[maybe_unused]] uint32_t from, uint32_t &to) {
		to = Version();
		std::vector<std::string>    Script{
		};

		for(const auto &i:Script) {
			try {
				auto Session = Pool_.get();
				Session << i , Poco::Data::Keywords::now;
			} catch (...) {

			}
		}
		return true;
	}
}

template<> void ORM::DB<Arilia::UELocatorRecordTuple, Arilia::LOCObjects::UELocationEntry>::Convert(const Arilia::UELocatorRecordTuple &In, Arilia::LOCObjects::UELocationEntry &Out) {
	Out.MAC = In.get<0>();
	Out.locations = OpenWifi::RESTAPI_utils::to_object_array<Arilia::LOCObjects::UELocation>(In.get<1>());
	Out.created = In.get<2>();
	Out.lastReport = In.get<3>();
}

template<> void ORM::DB<Arilia::UELocatorRecordTuple, Arilia::LOCObjects::UELocationEntry>::Convert(const Arilia::LOCObjects::UELocationEntry &In, Arilia::UELocatorRecordTuple &Out) {
	Out.set<0>(In.MAC);
	Out.set<1>(OpenWifi::RESTAPI_utils::to_string(In.locations));
	Out.set<2>(In.created);
	Out.set<3>(In.lastReport);
}
