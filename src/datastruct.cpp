/*
 * datastruct.cpp
 *
 *  Created on: Dec 17, 2020
 *      Author: Mickey
 */
#include "datastruct.h"

std::vector<Point> DataStruct::get_points() {
    std::vector<Point> v;
    v.reserve(points.size());
    std::copy(points.begin(), points.end(), std::back_inserter(v));

    return v;
}

int DataStruct::get_num_points() {

    return points.size();
}
