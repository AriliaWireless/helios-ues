//
// Created by stephane bourque on 2022-11-24.
//

#include "UEAggregator.h"
#include <framework/OpenWifiTypes.h>
#include <framework/KafkaManager.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

#include <nlohmann/json.hpp>

namespace Arilia {

    int UEAggregator::Start() {
        poco_information(Logger(),"Starting...");
        OpenWifi::Types::TopicNotifyFunction F = [this](const std::string &s1,const std::string &s2) { this->StateReceived(s1,s2); };
        WatcherId_ = OpenWifi::KafkaManager()->RegisterTopicWatcher(OpenWifi::KafkaTopics::STATE, F);
        AggregationThread_.start(*this);
        return 0;
    }

    void UEAggregator::Stop() {
        poco_information(Logger(),"Stopping...");
        Running_=false;
        OpenWifi::KafkaManager()->UnregisterTopicWatcher(OpenWifi::KafkaTopics::CONNECTION, WatcherId_);
        MessageQueue_.wakeUpAll();
        AggregationThread_.wakeUp();
        AggregationThread_.join();
        poco_information(Logger(),"Stopped...");
    }

    void UEAggregator::run() {
        OpenWifi::Utils::SetThreadName("cmd:mgr");
        Running_ = true;

        Poco::AutoPtr<Poco::Notification> NextMsg(MessageQueue_.waitDequeueNotification());
        while (NextMsg && Running_) {
            auto Msg = dynamic_cast<AggregationMessage *>(NextMsg.get());
            try {
                nlohmann::json Message = nlohmann::json::parse(Msg->Payload);

                if(Message.contains(OpenWifi::uCentralProtocol::SYSTEM)) {
                    auto System = Message[OpenWifi::uCentralProtocol::SYSTEM];
                }

                if(Message.contains(OpenWifi::uCentralProtocol::PAYLOAD)) {
                    auto Payload = Message[OpenWifi::uCentralProtocol::PAYLOAD];
                    if(Payload.contains("state")) {
                        auto State = Payload["state"];
                        auto Interfaces = State["interfaces"];
                        for(const auto &interface:Interfaces) {
                            const auto & ssids = interface["ssids"];
                            for(const auto &ssid:ssids) {
                                const auto & associations = ssid["associations"];
                                for(const auto &association:associations) {
                                    std::string Station = association["station"];
                                    std::cout << "Station: " << Station << std::endl;
                                }
                            }
                        }
                    }
                }

            } catch(const Poco::Exception &E) {
                Logger().log(E);
            } catch (...) {
                Logger().error("Exception in state reception loop");
            }
            NextMsg = MessageQueue_.waitDequeueNotification();
        }
    }

} // Arilia