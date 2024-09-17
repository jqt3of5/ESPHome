//
// Created by jqt3o on 9/16/2024.
//

#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
    namespace wen3410 {

        class WEN3410Component : public Component {
        public:
            void set_pin(GPIOPin *pin) { pin_ = pin; }

            void setup() override;
            void dump_config() override;
            float get_setup_priority() const override { return setup_priority::DATA; }

            void turn_off();
            void increase_speed();
            void increase_delay();

        protected:
            GPIOPin *pin_{nullptr};

            void writePreamble() const;
            void inline writeBlock(int16_t bits) const;
            void writeCommand(WenCommand command);
        };

    }  // namespace sps30
}  // namespace esphome
