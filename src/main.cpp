#include "Camera.h"
#include "Light.h"
#include "Ray.h"
#include "Sphere.h"
#include "Plane.h"

const unsigned int width = 640;
const unsigned int height = 480;
constexpr unsigned int aspectRatio = (float)width / (float)height;
unsigned int frameBuffer[width * height];

#ifdef __cplusplus
extern "C" {
#endif

void render() {
    Vec3 camPos{3, 1.5, -4};
    Vec3 lookAt{0, 0, 0};
    Vec3 camDir = Vec3{camPos - lookAt}.makeNegate().makeNormalize();
    Vec3 camRight = Vec3::cross(Vec3::up, camDir).makeNormalize();
    Vec3 camDown = Vec3::cross(camRight, camDir);

    Camera cam{camPos, camDir, camRight, camDown};
    Vec3 lightPos{-7, 10, -10};
    Light sceneLight{lightPos, Color::white};

    // scene object
    Sphere sceneSphere{Vec3::zero, 1, Color::green};
    Plane scenePlane{Vec3::up, -1, Color::purple};

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            unsigned int pixelPosition = width * x + y;

            if ((x > 200 && x < 440) && (y > 200 && y < 480)) {
                frameBuffer[pixelPosition] = 0xff17de0a;
            } else {
                frameBuffer[pixelPosition] = 0xff000000;
            }
        }
    }
}

#ifdef __cplusplus
}
#endif