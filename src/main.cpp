#include "Camera.h"
#include "Light.h"
#include "Ray.h"

const unsigned int width = 600;
const unsigned int height = 600;
unsigned int frameBuffer[width * height];

#ifdef __cplusplus
extern "C" {
#endif

void render() {
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