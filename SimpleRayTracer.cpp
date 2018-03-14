//
// Created by prof on 12.03.18.
//

#include <cfloat>
#include "SimpleRayTracer.h"
#include "Camera.h"


SimpleRayTracer::SimpleRayTracer(unsigned int m_MaxDepth):m_MaxDepth(m_MaxDepth) {}

void SimpleRayTracer::traceScene(const Scene &SceneModel, RGBImage &Image) {
    Camera c = Camera(-8, 1, 1, 0.75, 640, 480);
    for(unsigned int x = 0; x < Image.width(); ++x){
        for (unsigned int y = 0; y <  Image.height(); ++y) {
            Image.setPixelColor(x,y, trace(SceneModel, c.position(), c.generateRay(x,y), 0));
        }
    }
}

Color SimpleRayTracer::trace(const Scene &SceneModel, const Vector &o, const Vector &d, int depth) {

    float nearest_intersect = FLT_MAX;
    float s;
    Triangle temp_triangle;
    for (int i = 0; i < SceneModel.getTriangleCount(); ++i){

        temp_triangle = SceneModel.getTriangle(i);
        if(o.triangleIntersection(d, temp_triangle.A, temp_triangle.B, temp_triangle.C, s)){
            if(s < nearest_intersect)
                nearest_intersect = s;
        }
    }

    Vector intersect_point = o + d * nearest_intersect;

    for (int l = 0; l < SceneModel.getLightCount(); ++l) {

        Vector light_ray = (intersect_point - SceneModel.getLight(l).Position).normalize(); // nrmVector between light source and triangle to render
        bool light_coll = true;
        for (int i = 0; i < SceneModel.getTriangleCount(); ++i){

            temp_triangle = SceneModel.getTriangle(i);
            if(o.triangleIntersection(light_ray, temp_triangle.A, temp_triangle.B, temp_triangle.C, s)){
                if(s < nearest_intersect)
                    light_coll = false;
            }
        }
    }
    return temp_triangle.pMtrl->getDiffuseCoeff(o+d*s);
}

Color SimpleRayTracer::localIllumination(const Vector &SurfacePoint, const Vector &Eye, const Vector &Normal,
                                         const PointLight &Light, const Material &Material) {
    return Material.getDiffuseCoeff(SurfacePoint);
}

