//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "Audio.h"
#include <iostream>

namespace gb::frontend {
    Audio::Audio() {
        if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
            std::cerr << "Failed to initialize SDL Audio: " << SDL_GetError() << std::endl;
        }

        SDL_AudioSpec desired_spec;
        SDL_AudioSpec obtained_spec;

        SDL_zero(desired_spec);
        desired_spec.freq = 44100;
        desired_spec.format = AUDIO_F32SYS; // 32-bit Float
        desired_spec.channels = 2;          // Stereo (Left/Right)
        desired_spec.samples = 2048;        // Buffer size
        desired_spec.callback = nullptr;    // We will push audio manually via SDL_QueueAudio

        // Open the default audio device
        device_id = SDL_OpenAudioDevice(nullptr, 0, &desired_spec, &obtained_spec, 0);

        if (device_id == 0) {
            std::cerr << "Failed to open SDL Audio Device: " << SDL_GetError() << std::endl;
        } else {
            // Unpause the audio device to start playing
            SDL_PauseAudioDevice(device_id, 0);
        }
    }

    Audio::~Audio() {
        if (device_id != 0) {
            SDL_CloseAudioDevice(device_id);
        }
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }

    void Audio::push_samples(const std::vector<float>& samples) {
        if (samples.empty() || device_id == 0) return;

        Uint32 byte_size = samples.size() * sizeof(float);
        SDL_QueueAudio(device_id, samples.data(), byte_size);
    }
}