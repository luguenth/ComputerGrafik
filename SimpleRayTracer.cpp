//
// Created by prof on 12.03.18.
//

#include "SimpleRayTracer.h"


SimpleRayTracer::SimpleRayTracer(unsigned int m_MaxDepth):m_MaxDepth(m_MaxDepth) {}

void SimpleRayTracer::traceScene(const Scene &SceneModel, RGBImage &Image) {

}

Color SimpleRayTracer::trace(const Scene &SceneModel, const Vector &o, const Vector &d, int depth) {
    return Color();
}

Color SimpleRayTracer::localIllumination(const Vector &SurfacePoint, const Vector &Eye, const Vector &Normal,
                                         const PointLight &Light, const Material &Material) {
    return Color();
}

