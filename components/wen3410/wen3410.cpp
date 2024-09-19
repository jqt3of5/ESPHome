//
// Created by jqt3o on 9/16/2024.
//

#include "wen3410.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
    namespace wen3410 {

        static const char *const TAG = "wen3410";

        void WEN3410Component::setup() {
            ESP_LOGCONFIG(TAG, "Setting up TX 433Mhz for wen3410");
            this->pin_->setup();
            // clear bus with 480µs high, otherwise initial reset in search might fail
            this->pin_->pin_mode(gpio::FLAG_OUTPUT);
        }

        void WEN3410Component::dump_config() {
            ESP_LOGCONFIG(TAG, "TX 433Mhz for wen3410");
            LOG_PIN("  Pin: ", this->pin_);
        }

        void WEN3410Component::turn_off()  {
            ESP_LOGD(TAG, "Turning OFF.");
            writeCommand(WenCommand::Off);
        }

        void WEN3410Component::increase_delay() {
            ESP_LOGD(TAG, "increasing delay.");
            writeCommand(WenCommand::Time);
        }

        void WEN3410Component::increase_speed() {
            ESP_LOGD(TAG, "increasing speed.");
            writeCommand(WenCommand::Speed);
        }

        void WEN3410Component::writePreamble() const {
            for (int i = 0; i < 25; ++i)
            {
                pin_->digital_write(true);
                delayMicroseconds(300 + 30);

                pin_->digital_write(false);
                delayMicroseconds(340 - 30);
            }
        }

        void inline WEN3410Component::writeBlock(int16_t bits) const {
            for (int i = sizeof(bits)*8-1; i >= 0; i--)
            {
                bool v = bits & (1 << i);

                pin_.digital_write(true);
                delayMicroseconds(v ? 970 : 370);
                pin_.digital_write(false);
                delayMicroseconds(v ? 310: 910);
            }
        }

        void WEN3410Component::writeCommand(wen3410::WenCommand command) {

            writePreamble();
            delay(10);
            //The remote will repeat the command three times
            writeBlock(command);
            delay(10);
            writeBlock(command);
            delay(10);
            writeBlock(command);
        }
    }
}