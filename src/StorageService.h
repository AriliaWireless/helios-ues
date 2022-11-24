//
//	License type: BSD 3-Clause License
//	License copy: https://github.com/Telecominfraproject/wlan-cloud-ucentralgw/blob/master/LICENSE
//
//	Created by Stephane Bourque on 2021-03-04.
//	Arilia Wireless Inc.
//

#pragma once

#include "RESTObjects/RESTAPI_SecurityObjects.h"
#include "framework/StorageClass.h"

#include "Poco/Timer.h"
#include "storage/storage_uelocator.h"

namespace OpenWifi {

    class Archiver {
    public:
        void onTimer(Poco::Timer & timer);
    private:
    };

    class StorageService : public StorageClass {
    public:

        static auto instance() {
            static auto instance_ = new StorageService;
            return instance_;
        }

        int 	Start() override;
        void 	Stop() override;

        Arilia::UELocatorDB & UELocatorDB() { return *UELocatorDB_; }

	  private:
        std::unique_ptr<Arilia::UELocatorDB>           UELocatorDB_;
        Poco::Timer                     Timer_;
        Archiver                        Archiver_;
        std::unique_ptr<Poco::TimerCallback<Archiver>>   Archivercallback_;
   };

    inline auto StorageService() { return StorageService::instance(); };

}  // namespace
