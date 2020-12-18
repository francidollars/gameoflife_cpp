/*
 * ds_cellmap.cpp
 *
 *  Created on: Dec 17, 2020
 *      Author: Mickey
 */
#include "ds_cellmap.h"

DS_Cellmap::DS_Cellmap(unsigned int map_cols, unsigned int map_rows) {
    this->map_cols = map_cols;
    this->map_rows = map_rows;

    // Allocate map (bool**) according to given dimensions (cols, rows)
    this->map = (bool**) calloc(this->map_rows, sizeof(bool*));
    for (unsigned int h_index = 0; h_index < this->map_rows; h_index++)
        *(this->map + h_index) = (bool*) calloc(this->map_cols, sizeof(bool));

    // Initialize num_points as 0, declaring DataStruct initialized (> -1)
    this->points.clear();

}

bool** DS_Cellmap::cpy_map() {
    bool** old_map = (bool**) calloc(this->map_rows, sizeof(bool*));

    // Copy row by row
    for (unsigned int h_index = 0; h_index < this->map_rows; h_index++)
        *(old_map + h_index) = *(this->map + h_index);

    return old_map;
}

void DS_Cellmap::add_point(unsigned int x, unsigned int y) {
    if (this->map_cols <= x) {
        // Print statement for Debugging (will get rid of in time)
        // printf("WARNING:Call to SET_CELL out of bounds|x-range: %u >= %u\n", x, cellmap->width);

        return;
    } else if (this->map_rows <= y) {
        // Print statement for Debugging (will get rid of in time)
        // printf("WARNING:Call to SET_CELL out of bounds|y-range: %u >= %u\n", y, cellmap->height);

        return;
    }

    this->points.insert(Point((int) x, (int) y));
    *(*(this->map + y) + x) = true;

}

void DS_Cellmap::rem_point(unsigned int x, unsigned int y) {
    if (this->map_cols <= x) {
        // Print statement for Debugging (will get rid of in time)
        // printf("WARNING:Call to CLEAR_CELL out of bounds|x-range: %u >= %u\n", x, cellmap->width);

        return;
    } else if (this->map_rows <= y) {
        // Print statement for Debugging (will get rid of in time)
        // printf("WARNING:Call to CLEAR_CELL out of bounds|y-range: %u >= %u\n", y, cellmap->height);

        return;
    }

    this->points.erase(Point((int) x, (int) y));
    *(*(this->map + y) + x) = false;

}

// TODO Implement wrapping
bool DS_Cellmap::point_state(bool** ref_map, unsigned int x, unsigned int y) {
    if (this->map_cols <= x) {
        // Print statement for Debugging (will get rid of in time)
        // printf("WARNING:Call to CELL_STATE out of bounds|x-range: %u >= %u\n", x, cellmap->width);

        return false;
    } else if (this->map_rows <= y) {
        // Print statement for Debugging (will get rid of in time)
        // printf("WARNING:Call to CELL_STATE out of bounds|y-range: %u >= %u\n", y, cellmap->height);

        return false;
    }

    return *(*(ref_map + y) + x);
}

// TODO Implement wrapping
int DS_Cellmap::count_neighbors(bool** ref_map, unsigned int x, unsigned int y) {
    if (this->map_cols <= x) {
        // Print statement for Debugging (will get rid of in time)
        // printf("WARNING:Call to COUNT_NEIGHBORS out of bounds|x-range: %u >= %u\n", x, cellmap->width);

        return -1;
    } else if (this->map_rows <= y) {
        // Print statement for Debugging (will get rid of in time)
        // printf("WARNING:Call to COUNT_NEIGHBORS out of bounds|y-range: %u >= %u\n", y, cellmap->height);

        return -1;
    }

    int neighbor_count = point_state(ref_map, x - 1, y - 1) + point_state(ref_map, x, y - 1)
      + point_state(ref_map, x + 1, y - 1) + point_state(ref_map, x - 1, y) + point_state(ref_map, x + 1, y)
      + point_state(ref_map, x - 1, y + 1) + point_state(ref_map, x, y + 1) + point_state(ref_map, x + 1, y + 1);

    return neighbor_count;
}

// TODO Implement wrapping
void DS_Cellmap::next_generation(void) {
    int neighbor_count;

    bool** ref_map = cpy_map();

    for (unsigned int y = 0; y < this->map_rows; y++) {
        for (unsigned int x = 0; x < this->map_cols; x++) {
            neighbor_count = count_neighbors(ref_map, x, y);

            if (point_state(ref_map, x, y)) {
                if ((neighbor_count != 2) && (neighbor_count != 3))
                    rem_point(x, y);

            } else {
                if (neighbor_count == 3)
                    add_point(x, y);

            }
        }
    }

    free(ref_map);

}
