//
// Created by stephane bourque on 2022-11-24.
//

#pragma once

#include <framework/SubSystemServer.h>
#include <Poco/NotificationQueue.h>

namespace Arilia {

    class AggregationMessage: public Poco::Notification {
    public:
        AggregationMessage(const std::string &key,const std::string &payload) :
            Key(key),
            Payload(payload) {
        }
        std::string Key;
        std::string Payload;
    };

    class UEAggregator : public OpenWifi::SubSystemServer, Poco::Runnable {
    public:
        static auto instance() {
            auto instance_ = new UEAggregator;
            return instance_;
        }

        int Start() final;
        void Stop() final;
        inline void StateReceived(const std::string &key, const std::string &payload) {
            MessageQueue_.enqueueNotification(new AggregationMessage(key, payload));
        }
        void run() final;

    private:
        Poco::Thread    						AggregationThread_;
        Poco::NotificationQueue					MessageQueue_;
        std::uint64_t                           WatcherId_=0;
        volatile bool                           Running_=false;

        UEAggregator() noexcept:
                SubSystemServer("UEAggregator", "UE-AGGREGATOR", "aggregator")
        {
        }

    };

    inline auto UEAggregator() { return UEAggregator::instance(); }

};// Arilia

