//
//	License type: BSD 3-Clause License
//	License copy: https://github.com/Telecominfraproject/wlan-cloud-ucentralgw/blob/master/LICENSE
//
//	Created by Stephane Bourque on 2021-03-04.
//	Arilia Wireless Inc.
//

#include "StorageService.h"
#include "framework/MicroServiceFuncs.h"
#include "framework/utils.h"

namespace OpenWifi {

    int StorageService::Start() {
		std::lock_guard		Guard(Mutex_);
        poco_information(Logger(),"Starting...");

		StorageClass::Start();

        UELocatorDB_ = std::make_unique<Arilia::UELocatorDB>("UELocations", "uel", dbType_,*Pool_, Logger());
        UELocatorDB_->Create();

		Archivercallback_ = std::make_unique<Poco::TimerCallback<Archiver>>(Archiver_,&Archiver::onTimer);
		Timer_.setStartInterval( 5 * 60 * 1000);  // first run in 5 minutes
		Timer_.setPeriodicInterval(1 * 60 * 60 * 1000); // 1 hours
		Timer_.start(*Archivercallback_, MicroServiceTimerPool());

		return 0;
    }

    void StorageService::Stop() {
        poco_information(Logger(),"Stopping...");
        Timer_.stop();
        StorageClass::Stop();
        poco_information(Logger(),"Stopped...");
    }

    void Archiver::onTimer([[maybe_unused]] Poco::Timer &timer) {
        Utils::SetThreadName("strg-arch");

        std::uint64_t MaximumAge_ = MicroServiceConfigGetInt("archiver.maximumage",7);

        Poco::Logger &logger = Poco::Logger::get("STORAGE-ARCHIVER");
        logger.information("Squiggy the DB: removing old UEs.");
        StorageService()->UELocatorDB().RemoveOldUEs(MaximumAge_);
    }

}
// namespace