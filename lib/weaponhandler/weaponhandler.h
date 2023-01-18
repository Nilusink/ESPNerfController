#pragma once
#include <Arduino.h>


const char* charBoolean(bool b);

namespace wpn
{
    class Handler
    {
        private:
            int jPin, mPin;

            bool biometrics = false;
            bool jammer = false;
            bool mag = false;

        public:
            Handler(int jammerPin, int magPin);

            // utility functions
            void updateStates();

            // getters
            bool get_biometrics();

            bool get_jammer();

            bool get_mag();

            void get_as_json(char* buffer);
    };
}
