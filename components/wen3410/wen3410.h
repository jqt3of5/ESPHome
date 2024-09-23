//
// Created by jqt3o on 9/16/2024.
//

#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/entity_base.h"
#include "esphome/core/helpers.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
    namespace wen3410 {

        //The values indicate the number of times to repeat the command to set this value
        enum WenFilterSpeed {
            Low = 1,
            Medium = 2,
            High = 3,
        };

        //The values indicate the number of times to repeat the command to set this value
        enum WenFilterTime {
            None = 0,
            OneHour = 1,
            TwoHour = 2,
            FourHour = 3
        };

        enum WenCommand{
            Speed = 0b1100001110011110,
            Time = 0b1100001100110111,
            Off= 0b1100001110010001
        };


        class WEN3410 : public Component {
        public:
            void set_pin(GPIOPin *pin) { pin_ = pin; }
            void set_speed_button(sensor::Sensor *speed_button) { speedButton_ = speed_button; }
            void set_delay_button(sensor::Sensor * delay_button) { delayButton_ = delay_button; }
            void set_off_button(sensor::Sensor *off_button) { offButton_ = off_button }

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
            void writeCommand(wen3410::WenCommand command);

            button::Button * speedButton_ {nullptr};
            button::Button * delayButton_ {nullptr};
            button::Button * offButton_ {nullptr};

        };

    }  // namespace sps30
}  // namespace esphome
