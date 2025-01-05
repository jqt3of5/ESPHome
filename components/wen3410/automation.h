//
// Created by jqt3o on 9/18/2024.
//

#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "wen3410.h"

namespace esphome {
    namespace wen3410 {

        template<typename... Ts> class TurnOffAction : public Action<Ts...>, public Parented<WEN3410> {
        public:
            void play(Ts... x) override { this->parent_->turn_off(); }

        protected:
        };

        template<typename... Ts> class IncreaseSpeedAction : public Action<Ts...>, public Parented<WEN3410> {
        public:
            void play(Ts... x) override { this->parent_->increase_speed(); }

        protected:
        };


        template<typename... Ts> class IncreaseDelayAction : public Action<Ts...>, public Parented<WEN3410> {
        public:
            void play(Ts... x) override { this->parent_->increase_delay(); }

        protected:
        };


    }  // namespace sps30
}  // namespace esphome