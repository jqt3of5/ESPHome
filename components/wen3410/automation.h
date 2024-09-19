//
// Created by jqt3o on 9/18/2024.
//

#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "wen3410.h"

namespace esphome {
    namespace wen3410 {

        template<typename... Ts> class TurnOffAction : public Action<Ts...> {
        public:
            explicit TurnOffAction(WEN3410Component *wen3410) : wen3410_(wen3410) {}

            void play(Ts... x) override { this->wen3410_->turn_off(); }

        protected:
            WEN3410Component *wen3410_;
        };

        template<typename... Ts> class IncreaseSpeedAction : public Action<Ts...> {
        public:
            explicit IncreaseSpeedAction(WEN3410Component *wen3410) : wen3410_(wen3410) {}

            void play(Ts... x) override { this->wen3410_->increase_speed(); }

        protected:
            WEN3410Component *wen3410_;
        };


        template<typename... Ts> class IncreaseDelayAction : public Action<Ts...> {
        public:
            explicit IncreaseDelayAction(WEN3410Component *wen3410) : wen3410_(wen3410) {}

            void play(Ts... x) override { this->wen3410_->increase_delay(); }

        protected:
            WEN3410Component *wen3410_;
        };


    }  // namespace sps30
}  // namespace esphome