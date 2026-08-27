//
// Created by Andreas Sabelfeld on 27.08.2026.
//

#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#include "Joypad.h"

namespace gb::frontend {
    class Renderer {
    public:
        Renderer(int scale = 4);
        ~Renderer();

        // Returns false if the user clicked the 'X' to close the window
        bool poll_events(gb::core::Joypad& joypad);

        // Pushes the PPU buffer to the screen
        void render_frame(const uint32_t* pixel_buffer);

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;

        const int GB_WIDTH = 160;
        const int GB_HEIGHT = 144;
    };
}