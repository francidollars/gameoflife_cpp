/*
 * ds_cellmap.h
 *
 *  Created on: Dec 17, 2020
 *      Author: Mickey
 */
#ifndef DS_CELLMAP_H_
#define DS_CELLMAP_H_

#include "datastruct.h"

class DS_Cellmap : public DataStruct {
private:
    bool** map;
    unsigned int map_cols;
    unsigned int map_rows;

    bool** cpy_map(void);

    /**
    * Returns cell state (true = on | false = off).
    */
    bool point_state(bool** ref_map, unsigned int x, unsigned int y);

    /**
    * Returns the number of neighbors a specified cell has.
    */
    int count_neighbors(bool** ref_map, unsigned int x, unsigned int y);

public:
    /**
    * Initializes current and next cellmaps for the game to be played.
    */
    DS_Cellmap(unsigned int num_cols, unsigned int num_rows);

    /**
    * Frees memory where cellmap exists
    */
    // ~DS_Cellmap(); TODO may be necessary

    /**
    * Turns cell on at screen position (x, y).
    */
    void add_point(unsigned int x, unsigned int y);

    /**
    * Turns cell off at screen position (x, y).
    */
    void rem_point(unsigned int x, unsigned int y);

    /**
     * 
     */
    void next_generation(void);

};

#endif /* DS_CELLMAP_H_ */
