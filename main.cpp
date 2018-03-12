#include <iostream>
#include "CGUtilities.h"
#include "rgbimage.h"
#include "SimpleRayTracer.h"


int main(int argc, const char * argv[]) {

    Scene ModelScene(0);
    RGBImage Image(640,480);
    SimpleRayTracer Raytracer(2);
    Raytracer.traceScene(ModelScene, Image);
    Image.saveToDisk("raytracing_image.bmp");
    return 0;
}
