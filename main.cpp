#include <iostream>
#include "CGUtilities.h"
#include "RGBImage.h"
#include "SimpleRayTracer.h"


int main(int argc, const char * argv[]) {

    Scene ModelScene(0);
    RGBImage Image(1920,1080);
    SimpleRayTracer Raytracer(2);
    Raytracer.traceScene(ModelScene, Image);
    Image.saveToDisk("raytracing_image.bmp");
    return 0;
}
