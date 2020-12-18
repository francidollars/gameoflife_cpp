/**
 * datastruct.h
 *
 *  Created on: Dec 17, 2020
 *      Author: Mickey
 */
#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#include <cstdlib>
#include <vector>
#include <set>

typedef struct Point {
    int x{ -1 };
    int y{ -1 };

    Point(int x, int y)
        : x{ x }, y{ y } { }
    ~Point() = default;

    bool operator <(const Point& pt) const {

        return (x < pt.x) || ((!(pt.x < x)) && (y < pt.y));
    }

} Point;

class DataStruct {
protected:
    std::set<Point> points{ };

public:
    // DataStruct();
    virtual ~DataStruct() = default;

    std::vector<Point> get_points(void);

    int get_num_points(void);

    void print_points(void);

    virtual void add_point(unsigned int x, unsigned int y) = 0;

    virtual void rem_point(unsigned int x, unsigned int y) = 0;

    virtual void next_generation(void) = 0;

};

#endif /* DATASTRUCT_H_ */
