//
// Created by prof on 12.03.18.
//

#ifndef CG1_SIMPLERAYTRACER_H
#define CG1_SIMPLERAYTRACER_H


#include "CGUtilities.h"
#include "RGBImage.h"

class SimpleRayTracer {
public:
    SimpleRayTracer(unsigned int m_MaxDepth);
    void traceScene(const Scene& SceneModel, RGBImage& Image);

protected:
    Color trace(const Scene& SceneModel, const Vector& o, const Vector& d, int depth);
    Color localIllumination(const Vector& SurfacePoint, const Vector& Eye, const Vector& Normal, const PointLight& Light, const Material& Material);
    unsigned int m_MaxDepth;
};


#endif //CG1_SIMPLERAYTRACER_H
