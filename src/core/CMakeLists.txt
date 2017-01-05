add_library(core
        base/IShape.cpp base/IShape.h
        base/IAggregate.cpp base/IAggregate.h
        base/ICamera.cpp base/ICamera.h
        base/ISampler.cpp base/ISampler.h
        base/IFilter.cpp base/IFilter.h
        Film.cpp Film.h
        base/IMaterial.cpp base/IMaterial.h
        base/ITexture.cpp base/ITexture.h
        base/ILight.cpp
        Transform.h Transform.cpp
        utils/Constants.h
        utils/SceneContext.h
        utils/UnitUtils.h
        base/IMedium.cpp base/IMedium.h
        base/IIntegrator.cpp base/IIntegrator.h
        BBox.cpp BBox.h)

target_link_libraries(core geometry)

