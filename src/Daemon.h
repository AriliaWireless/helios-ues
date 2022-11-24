//
//	License type: BSD 3-Clause License
//	License copy: https://github.com/Telecominfraproject/wlan-cloud-ucentralgw/blob/master/LICENSE
//
//	Created by Stephane Bourque on 2021-03-04.
//	Arilia Wireless Inc.
//

#pragma once

#include <array>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>

#include "framework/MicroServiceNames.h"
#include "framework/MicroService.h"

#include "Dashboard.h"
#include "framework/OpenWifiTypes.h"
#include "UELocatorWebSocketClient.h"

#include "ar_framework/MicroServicesNames.h"

namespace OpenWifi {

	[[maybe_unused]] static const char * vDAEMON_PROPERTIES_FILENAME = "owuelocator.properties";
	[[maybe_unused]] static const char * vDAEMON_ROOT_ENV_VAR = "OWUELOCATOR_ROOT";
	[[maybe_unused]] static const char * vDAEMON_CONFIG_ENV_VAR = "OWUELOCATOR_CONFIG";
	[[maybe_unused]] static const char * vDAEMON_APP_NAME = Arilia::uUELocatorServiceName.c_str();
	[[maybe_unused]] static const uint64_t vDAEMON_BUS_TIMER = 10000;

    class Daemon : public MicroService {
		public:
			explicit Daemon(const std::string & PropFile,
							const std::string & RootEnv,
							const std::string & ConfigEnv,
							const std::string & AppName,
						  	uint64_t 	BusTimer,
							const SubSystemVec & SubSystems) :
				MicroService( PropFile, RootEnv, ConfigEnv, AppName, BusTimer, SubSystems) {};

			static Daemon *instance();
			inline DeviceDashboard	& GetDashboard() { return DB_; }
			Poco::Logger & Log() { return Poco::Logger::get(AppName()); }
			void PostInitialization(Poco::Util::Application &self);
	  	private:
			DeviceDashboard				                    DB_;
			std::unique_ptr<UELocatorWebSocketClient>       WebSocketProcessor_;
    };

	inline Daemon * Daemon() { return Daemon::instance(); }
	void DaemonPostInitialization(Poco::Util::Application &self);
}

