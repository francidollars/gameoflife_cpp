/*
 * main.cpp
 *
 *  Created on: Dec 18, 2020
 *      Author: Mickey
 */
#include "sdl_funcs.h"
#include "datastruct.h"
#include "ds_cellmap.h"
#include <iostream>

int main(int argc, char** argv) {
    SDL_SysMgr sdl_mgr = SDL_SysMgr();
    sdl_mgr.init_sdl(640, 480);

    DataStruct* ds = new DS_Cellmap(640, 480);

    int x{}, y{};
    int event_num = -1;
    while((event_num = sdl_mgr.input_handler(&x, &y))) {
        if (event_num > 2)
            ds->add_point(x, y);

        sdl_mgr.prepare_scene((SDL_Point*) ds->get_points().data(), ds->get_num_points());
        sdl_mgr.present_scene();
    }

    return 0;
}
