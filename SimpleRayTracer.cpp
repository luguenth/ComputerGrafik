//
// Created by prof on 12.03.18.
//

#include "SimpleRayTracer.h"
#include "Camera.h"


SimpleRayTracer::SimpleRayTracer(unsigned int m_MaxDepth):m_MaxDepth(m_MaxDepth) {}

void SimpleRayTracer::traceScene(const Scene &SceneModel, RGBImage &Image) {
    Camera c = Camera(-8, 1, 1, 0.75, 640, 480);
    for(unsigned int x = 0; x < Image.width(); ++x){
        for (unsigned int y = 0; y <  Image.height(); ++y) {
            Image.setPixelColor(x,y, trace(SceneModel, c.position(), c.generateRay(x,y), m_MaxDepth));
        }
    }
}

Color SimpleRayTracer::trace(const Scene &SceneModel, const Vector &o, const Vector &d, int depth) {
    for (int i = 0; i < SceneModel.getTriangleCount(); ++i){
        Triangle temp = SceneModel.getTriangle(i);
        float s;
        if(o.triangleIntersection(d, temp.A, temp.B, temp.C, s)){
            if(depth != 0)
                trace(SceneModel,(o + d*s), d.reflection(temp.B.cross(temp.A)), --depth);
            return temp.pMtrl->getDiffuseCoeff(o+d*s);
        }
    }
    return Color();
}

Color SimpleRayTracer::localIllumination(const Vector &SurfacePoint, const Vector &Eye, const Vector &Normal,
                                         const PointLight &Light, const Material &Material) {
    return Material.getDiffuseCoeff(SurfacePoint);
}

