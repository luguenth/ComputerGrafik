//
// Created by prof on 12.03.18.
//

#include <cfloat>
#include <cmath>
#include "SimpleRayTracer.h"
#include "Camera.h"


SimpleRayTracer::SimpleRayTracer(unsigned int m_MaxDepth):m_MaxDepth(m_MaxDepth) {}

void SimpleRayTracer::traceScene(const Scene &SceneModel, RGBImage &Image) {
    Camera c = Camera(-8, 1, 1, 0.75, 640, 480);
    for(unsigned int x = 0; x < Image.width(); ++x){
        for (unsigned int y = 0; y <  Image.height(); ++y) {
            Image.setPixelColor(x,y, Color());
            Image.setPixelColor(x,y, trace(SceneModel, c.position(), c.generateRay(x,y), 2));
        }
    }
}

Color SimpleRayTracer::trace(const Scene &SceneModel, const Vector &o, const Vector &d, int depth) {

    float nearest_intersect = FLT_MAX;
    float s;
    Triangle temp_triangle;
    Color temp_color;
    Vector intersect_point;
    int temp_i = 0;
    for (int i = 0; i < SceneModel.getTriangleCount(); ++i){

        temp_triangle = SceneModel.getTriangle(i);
        if(o.triangleIntersection(d, temp_triangle.A, temp_triangle.B, temp_triangle.C, s)){
            if(s < nearest_intersect) {
                nearest_intersect = s;
                intersect_point = o + d * nearest_intersect;
                temp_i = i;
            }
        }
    }

    temp_triangle = SceneModel.getTriangle(temp_i);
    for (int l = 0; l < SceneModel.getLightCount(); ++l) {
        if(true){
            temp_color += localIllumination(
                    intersect_point,
                    o,
                    temp_triangle.calcNormal(intersect_point),
                    SceneModel.getLight(l),
                    *temp_triangle.pMtrl);
        }
    }
//    for (int l = 0; l < SceneModel.getLightCount(); ++l) {
//
//        Vector light_ray = (intersect_point - SceneModel.getLight(l).Position).normalize(); // nrmVector between light source and triangle to render
//        bool light_coll = true;
//        for (int i = 0; i < SceneModel.getTriangleCount(); ++i){
//
//            temp_triangle = SceneModel.getTriangle(i);
//            if(o.triangleIntersection(light_ray, temp_triangle.A, temp_triangle.B, temp_triangle.C, s)){
//                if(s < nearest_intersect)
//                    light_coll = false;
//            }
//        }
//        if(light_coll) {
//            Vector SceneLight = intersect_point - SceneModel.getLight(l).Position;
//            Vector ab = temp_triangle.B - temp_triangle.A;
//            Vector ac = temp_triangle.C - temp_triangle.A;
//            Vector nrm = ab.cross(ac);
//            temp_color += temp_triangle.pMtrl->getDiffuseCoeff(intersect_point) * SceneModel.getLight(l).Intensity *
//                          cos(nrm.dot(SceneLight)/nrm.length()*SceneLight.length());
//        } else {
//            temp_color = Color();
//        }
//    }

    return temp_color;
}

Color SimpleRayTracer::localIllumination(const Vector &SurfacePoint, const Vector &Eye, const Vector &Normal,
                                         const PointLight &Light, const Material &Material) {
    return Material.getDiffuseCoeff(SurfacePoint);
}

