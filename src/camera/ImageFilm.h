//
// Created by lejonmcgowan on 11/26/16.
//

#ifndef JOHNNYRENDERER2_IMAGEFILM_H
#define JOHNNYRENDERER2_IMAGEFILM_H


#include <core/IFilm.h>
#include <string>

class ImageFilm: public IFilm
{
private:
    std::string name;
public:
    ImageFilm(const Vec2& resXY, std::string filename);

};


#endif //JOHNNYRENDERER2_IMAGEFILM_H
