//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "Renderer.h"

namespace gb::frontend {
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

}