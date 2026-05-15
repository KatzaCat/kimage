#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include "kimage.hpp"

#include <vector>

int main() {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_Window *window = SDL_CreateWindow("BMP_SDL", 1280, 720, 0);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

        bool is_running = true;

        k::Image image("images/BMP32bit.bmp");
        std::vector<unsigned char> pixel_date = image.getData();
        unsigned char *raw_pixel_data = pixel_date.data();

        SDL_Surface *surface = SDL_CreateSurfaceFrom(
                image.getWidth(), image.getHeight(),
                SDL_PIXELFORMAT_RGBA32,
                raw_pixel_data,
                image.getWidth() * 4
        );

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        float texture_width = surface->w * 20;
        float texture_height = surface->h * 20;

        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

        SDL_FRect destination_rect = {};

        destination_rect.x = static_cast<float>((1280 - texture_width) / 2);
        destination_rect.y = static_cast<float>((720 - texture_height) / 2);
        destination_rect.w = texture_width;
        destination_rect.h = texture_height;

        while (is_running) {
                SDL_Event event;
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                                case SDL_EVENT_QUIT:
                                        is_running = false;
                                        break;

                                default: break;
                        }
                }

                SDL_SetRenderDrawColor(renderer, 125, 150, 200, 255);
                SDL_RenderClear(renderer);

                SDL_RenderTexture(renderer, texture, NULL, &destination_rect);

                SDL_RenderPresent(renderer);
        }

        SDL_DestroySurface(surface);
        SDL_DestroyTexture(texture);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);

        SDL_Quit();

        return 0;
}
