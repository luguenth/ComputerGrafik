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
    if(depth<=0) {
        return Color();
    }
    float nearest_intersect = FLT_MAX;
    float s = FLT_MAX;
    Triangle temp_triangle;
    Color temp_color = Color();
    Vector intersect_point;
    int temp_i = 0;
    for (int i = 0; i < SceneModel.getTriangleCount(); ++i){

        temp_triangle = SceneModel.getTriangle(i);
        if(o.triangleIntersection(d, temp_triangle.A, temp_triangle.B, temp_triangle.C, s)){
            if(s < nearest_intersect) {
                nearest_intersect = s;

                temp_i = i;
            }
        }
    }
    if(temp_i == -1)
        return temp_color;

    intersect_point = o + d * nearest_intersect;
    temp_triangle = SceneModel.getTriangle(temp_i);

    for (int l = 0; l < SceneModel.getLightCount() && (s != FLT_MAX); ++l) {

        bool visible = true;
        Vector light_position = SceneModel.getLight(l).Position;
        Vector between_pos_light = light_position - intersect_point;
        float distance = between_pos_light.length();
        between_pos_light.normalize();

        for (int i = 0; i < SceneModel.getTriangleCount() && visible; ++i) {

            Triangle angle_iter = SceneModel.getTriangle(i);

            if(intersect_point.triangleIntersection(between_pos_light, angle_iter.A, angle_iter.B, angle_iter.C, s)){
                if(distance > s && s > 0.f)
                    visible = false;
            }

        }

        if(visible){
            temp_color += localIllumination(
                    intersect_point,
                    o,
                    temp_triangle.calcNormal(intersect_point),
                    SceneModel.getLight(l),
                    *temp_triangle.pMtrl);



        }
    }
    if(temp_triangle.pMtrl->getReflectivity(intersect_point) == 0){
        return temp_color;
    }
    Vector reflection_vector = d.reflection(temp_triangle.calcNormal(intersect_point));

    temp_color += trace(SceneModel,
                        intersect_point,
                        reflection_vector.normalize(),
                        --depth)
                  * temp_triangle.pMtrl->getReflectivity(intersect_point);

    //Maybe add transmission here
    if(temp_color.R == 0, temp_color.G == 0, temp_color.B == 0)
        temp_color = Color(255,255,255);
    return temp_color;
}

Color SimpleRayTracer::localIllumination(const Vector &SurfacePoint, const Vector &Eye, const Vector &Normal,
                                         const PointLight &Light, const Material &Material) {
    Vector L = Light.Position - SurfacePoint;

    Color diffuseComp = Light.Intensity * Material.getDiffuseCoeff(SurfacePoint) * fmax(0, Normal.dot(L) / (Normal.length() * L.length()));

    Vector E = Eye - SurfacePoint;
    Vector R = (-L).reflection(Normal);

    Color specularComp = Light.Intensity * Material.getSpecularCoeff(SurfacePoint) * powf(fmax(0, E.dot(R) / (E.length() * R.length())), Material.getSpecularExp(SurfacePoint));

    return diffuseComp + specularComp;
}

