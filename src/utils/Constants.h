//
// Created by lejonmcgowan on 12/28/16.
//

#ifndef JOHNNYRENDERER2_CONSTUTILS_H
#define JOHNNYRENDERER2_CONSTUTILS_H
namespace Constants
{
    const float machineEpsilon = std::numeric_limits<float>::epsilon() * 0.5f;
    inline const float gamma(int n)
    {
        return (n * machineEpsilon) / (1 - n * machineEpsilon);
    }

    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique( Args&& ...args )
    {
        return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
    }

}
#endif //JOHNNYRENDERER2_CONSTUTILS_H
