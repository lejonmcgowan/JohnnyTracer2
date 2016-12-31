//
// Created by lejonmcgowan on 12/28/16.
//

#include <geometry/shapes/Sphere.h>
#include <geometry/shapes/Box.h>
#include <geometry/shapes/Plane.h>
#include <geometry/shapes/Triangle.h>
#include <light/PointLight.h>
#include <camera/PerspectiveCamera.h>
#include <camera/BoxFilter.h>
#include <utils/Constants.h>
#include "POVElemParser.h"

Transform parseTransform(SceneElem elem)
{
    Vec3 rotate, translate, scale;
    std::array<Number, 3> temp;

    if (elem.hasMod("rotate"))
    {
        SceneElemMod::ModData modData = elem.getMod("rotate").getData();
        std::copy(std::begin(modData.vec3), std::end(modData.vec3), temp.begin());
        rotate[0] = temp[0];
        rotate[1] = temp[1];
        rotate[2] = temp[2];
    }
    if (elem.hasMod("translate"))
    {
        SceneElemMod::ModData modData = elem.getMod("translate").getData();
        std::copy(std::begin(modData.vec3), std::end(modData.vec3), temp.begin());
        translate[0] = temp[0];
        translate[1] = temp[1];
        translate[2] = temp[2];
    }

    if (elem.hasMod("scale"))
    {
        SceneElemMod::ModData modData = elem.getMod("scale").getData();
        std::copy(std::begin(modData.vec3), std::end(modData.vec3), temp.begin());
        scale[0] = temp[0];
        scale[1] = temp[1];
        scale[2] = temp[2];
    }

    Transform transform;
    transform.scaleBy(scale);
    transform.rotateBy(rotate);
    transform.translateBy(translate);

    return transform;
}

Vec3 getVec3(SceneElem elem, std::string name)
{
    std::array<Number, 3> dataArray;
    const SceneElemMod::ModData& modData = elem.getMod(name).getData();
    std::copy(std::begin(modData.vec3), std::begin(modData.vec3), dataArray.begin());
    Vec3 vec;
    vec[0] = dataArray[0];
    vec[1] = dataArray[1];
    vec[2] = dataArray[2];

    return vec;
}

Vec3 getVec3(SceneElemMod elem, std::string name)
{
    std::array<Number, 3> dataArray;
    const SceneElemMod::ModData& modData = elem.getMod(name).getData();
    std::copy(std::begin(modData.vec3), std::begin(modData.vec3), dataArray.begin());
    Vec3 vec;
    vec[0] = dataArray[0];
    vec[1] = dataArray[1];
    vec[2] = dataArray[2];

    return vec;
}

Sphere parseSphere(SceneElem elem)
{
    Transform transform = parseTransform(elem);
    Vec3 center = getVec3(elem, "center");

    transform.translateBy(center);
    return Sphere((Number) elem.getMod("radius").getData().dbl, transform);
}

Box parseBox(SceneElem elem)
{
    Transform transform = parseTransform(elem);
    Vec3 boxMin = getVec3(elem, "min");
    Vec3 boxMax = getVec3(elem, "max");

    return Box(boxMin, boxMax, transform);
}

Plane parsePlane(SceneElem elem)
{
    Vec3 normal = getVec3(elem, "normal");
    double normalProjection = elem.getMod("d").getData().dbl;
    return Plane(normal, normalProjection);
}

Triangle parseTriangle(SceneElem elem)
{
    Transform transform = parseTransform(elem);
    Vec3 a = getVec3(elem, "a");
    Vec3 b = getVec3(elem, "b");
    Vec3 c = getVec3(elem, "c");
    return Triangle(a, b, c, transform);
}

std::unique_ptr<ICamera> POVElemParser::parseCamera(SceneElem elem)
{
    Transform transform;
    BoxFilter basicFilter(Vec2(1, 1));
    Film basicFilm(Vec2(100, 100), basicFilter, "res/scenes/test.pov");

    return Constants::make_unique<PerspectiveCamera>(transform, basicFilm, transform, Vec4());
}

std::unique_ptr<ILight> POVElemParser::parseLight(SceneElem elem)
{
    return Constants::make_unique<PointLight>(Transform(), Color());
}

std::unique_ptr<IShape> POVElemParser::parseShape(SceneElem elem)
{
    if (elem.name == "sphere")
    {
        Sphere sphere = parseSphere(elem);
        return std::unique_ptr<Sphere>(&sphere);
    }
    else if (elem.name == "triangle")
    {
        Triangle triangle = parseTriangle(elem);
        return std::unique_ptr<Triangle>(&triangle);
    }
    else if (elem.name == "box")
    {
        Box box = parseBox(elem);
        return std::unique_ptr<Box>(&box);
    }
    else
        std::runtime_error("Unsupported POV shape: " + elem.name);

    assert(false);
}

/**
 * In this case, this is used to parse planes into the SceneCreator
 * Note that, once again, use of this structure should be minimized
 * @param elem elem to parse
 * @param sceneCreator scene creator to give parser direct access to
 */
void POVElemParser::parseCustom(SceneElem elem, SceneCreator& sceneCreator)
{
    if (elem.name == "plane")
    {
        Plane plane = parsePlane(elem);
        //todo add plane to sceneCreator
    }
    else
    {
        std::runtime_error("Unsupported POV shape: " + elem.name);
    }
}
