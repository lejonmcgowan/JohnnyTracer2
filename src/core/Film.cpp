//
// Created by lejonmcgowan on 9/4/16.
//

#include "Film.h"

Film::Film(Vec2 resolution, IFilter& filter, std::string filename):
    res(resolution),filename(filename)
{
    this->filter.reset(&filter);
}
