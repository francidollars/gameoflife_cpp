/*
 * sdl_funcs.h
 *
 *  Created on: Jan 1, 2020
 *      Author: Mickey
 */
#ifndef SDL_FUNCS_H_
#define SDL_FUNCS_H_

#include "SDL_FontCache.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class SDL_SysMgr {
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Event events;
        FC_Font* font;
        // int ref_rate;
        // bool running;
    public:
        SDL_SysMgr();
        ~SDL_SysMgr();

        bool init_sdl(unsigned int win_width, unsigned int win_height);

        int input_handler(int* x, int* y);

        void prepare_scene(SDL_Point* points, int num_points);

        void present_scene(void);

        char* get_time(int time);
};

#endif /* SDL_FUNCS_H_ */