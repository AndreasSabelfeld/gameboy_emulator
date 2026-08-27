//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "Renderer.h"
#include <iostream>

namespace gb::frontend {
    Renderer::Renderer(int scale) {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return;
        }

        window = SDL_CreateWindow(
            "Game Boy Emulator",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            GB_WIDTH * scale, GB_HEIGHT * scale,
            SDL_WINDOW_SHOWN
        );

        // Hardware accelerated renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        // Ensure scale quality is nearest-neighbor for crisp pixels
        SDL_RenderSetLogicalSize(renderer, GB_WIDTH, GB_HEIGHT);

        // ARGB8888 matches your 0xAARRGGBB format from get_color()
        texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            GB_WIDTH, GB_HEIGHT
        );
    }

    Renderer::~Renderer() {
        if (texture) SDL_DestroyTexture(texture);
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool Renderer::poll_events(gb::core::Joypad& joypad) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false; // User closed the window
            }
            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                bool is_pressed = (event.type == SDL_KEYDOWN);
                bool is_dpad = false;
                uint8_t bit = 0;
                bool valid_key = true;

                switch (event.key.keysym.sym) {
                    // D-Pad
                    case SDLK_d: is_dpad = true; bit = 0; break;
                    case SDLK_a: is_dpad = true; bit = 1; break;
                    case SDLK_w: is_dpad = true; bit = 2; break;
                    case SDLK_s: is_dpad = true; bit = 3; break;

                        // Action Buttons
                    case SDLK_p:         is_dpad = false; bit = 0; break; // A
                    case SDLK_o:         is_dpad = false; bit = 1; break; // B
                    case SDLK_COMMA:     is_dpad = false; bit = 2; break; // Select
                    case SDLK_PERIOD:    is_dpad = false; bit = 3; break; // Start
                    default: valid_key = false; break;
                }

                if (valid_key) {
                    if (is_pressed) {
                        joypad.press_button(is_dpad, bit);
                    } else {
                        joypad.release_button(is_dpad, bit);
                    }
                }
            }
        }
        return true;
    }

    void Renderer::render_frame(const uint32_t* pixel_buffer) {
        // Copy the PPU's buffer directly into the SDL texture
        SDL_UpdateTexture(texture, nullptr, pixel_buffer, GB_WIDTH * sizeof(uint32_t));

        // Clear, copy, and swap buffers
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
}