//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once

#include <vector>
#include <SDL.h>

namespace gb::frontend {
    class Audio {
    public:
        Audio();
        ~Audio();

        void push_samples(const std::vector<float>& samples);

    private:
        SDL_AudioDeviceID device_id;
    };
}