/*
 * sdl_funcs.cpp
 *
 *  Created on: Dec 17, 2020
 *      Author: Mickey
 */
#include "sdl_funcs.h"

SDL_SysMgr::SDL_SysMgr() {
    window = nullptr;
    renderer = nullptr;
}

SDL_SysMgr::~SDL_SysMgr() {
    FC_FreeFont(font);
    SDL_Quit();

}

bool SDL_SysMgr::init_sdl(unsigned int win_width, unsigned int win_height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("SDL initialization failed:\n\t%s\n", SDL_GetError());

		return false;
	}

    // Initialize SDL_Window
	window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);

    SDL_SetWindowResizable(window, (SDL_bool) false);

    // Check SDL_window for errors
	if (!window || (SDL_GetWindowSurface(window)->w != win_width)
      || (SDL_GetWindowSurface(window)->h != win_height)) {
		SDL_Log("Failed to create %d x %d window:\n\t%s\n", win_width, win_height, SDL_GetError());

		return false;
	}

    // Initialize SDL_Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, win_width, win_height);

    // Check SDL_Renderer for errors
	if (!renderer) {
		SDL_Log("Failed to create renderer:\n\t%s\n", SDL_GetError());

		return false;
	}

    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear") != SDL_TRUE) {
        SDL_Log("Failed to set hinting:\n\t%s\n", SDL_GetError());

        return false;
    }

    SDL_DisplayMode display_mode;

    for (int i = 0; i < SDL_GetNumVideoDisplays(); i++) {
        if (SDL_GetCurrentDisplayMode(i, &display_mode) != 0) {
            // In case of error...
            SDL_Log("Could not get display mode for video display #%d:\n\t%s\n", i, SDL_GetError());
        } else {
            // On success, print the current display mode.
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, display_mode.w, display_mode.h,
              display_mode.refresh_rate);
        }
    }

    if (TTF_Init() < 0) {
		printf("TTF initialization failed:\n\t%s\n", TTF_GetError());

		return false;
	}

    // TODO Dynamically select font
    font = FC_CreateFont();
    FC_LoadFont(font, renderer, "/usr/share/fonts/liberation/LiberationMono-Regular.ttf",
      11, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);

    if (!font) {
        printf("TTF_Font call failed:\n\t%s\n", TTF_GetError());

        return false;
    }

    return true;
}

int SDL_SysMgr::input_handler(int* x, int* y) {
    int event_num = -1;

    while (SDL_PollEvent(&(events))) {
        switch (events.type) {
            case SDL_QUIT:
                event_num = 0;
                break;
            case SDL_MOUSEMOTION:
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                    *x = events.motion.x;
                    *y = events.motion.y;
                    event_num = 3;
                }
                break;
            case SDL_KEYDOWN:
                switch (events.key.keysym.sym) {
                    case SDLK_SPACE:
                        event_num = 2;
                        break;
                    default:
                        break;
                }
        }
    }

    return event_num;
}

void SDL_SysMgr::prepare_scene(SDL_Point* points, int num_points) {
    // Set background to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Set pixel color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawPoints(renderer, points, num_points);

}

void SDL_SysMgr::present_scene() {
    SDL_RenderPresent(renderer);

}

/*
char* get_time(int time) {
    static char run_clock[9] = "";

    snprintf(run_clock, sizeof(run_clock), "%02d:%02d:%02d", (time / 3600000) % 60,
	  (time / 60000) % 60, (time / 1000) % 60);

    return run_clock;
}
*/
