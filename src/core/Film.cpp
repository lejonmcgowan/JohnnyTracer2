//
// Created by lejonmcgowan on 9/4/16.
//

#include "Film.h"

Film::Film(Vec2 resolution, std::unique_ptr<IFilter>& filter, std::string filename):
    res(resolution),filename(filename),filter(std::move(filter))
{
}
