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

    void Renderer::render_frame(const uint32_t* pixel_buffer) {
        // Copy the PPU's buffer directly into the SDL texture
        SDL_UpdateTexture(texture, nullptr, pixel_buffer, GB_WIDTH * sizeof(uint32_t));

        // Clear, copy, and swap buffers
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
}