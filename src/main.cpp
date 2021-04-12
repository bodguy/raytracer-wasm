#include "Camera.h"
#include "Light.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include <algorithm>
#include <vector>

const unsigned int width = 640;
const unsigned int height = 480;
constexpr float aspectRatio = (float)width / (float)height;
unsigned int frameBuffer[width * height];

int winningObjectIndex(const std::vector<float> &intersections) {
  if (intersections.empty()) {
    return -1;
  }

  if (intersections.size() == 1) {
    if (intersections[0] > 0) {
      return 0;
    } else {
      return -1;
    }
  }

  // find maximum value
  float max = *std::max_element(std::begin(intersections), std::end(intersections));
  // then start from the max value find min positive value
  if (max > 0) {
    auto pos = std::min_element(std::begin(intersections), std::end(intersections),
                                [](const float t1, const float t2) {
                                  return t1 > 0 && (t2 <= 0 || t1 < t2);
                                });
    return std::distance(std::begin(intersections), pos);
  }

  // all the intersections were negative
  return -1;
}

#ifdef __cplusplus
extern "C" {
#endif

void render() {
  Vec3 camPos{3, 1.5, -4};
  Vec3 lookAt{0, 0, 0};
  Vec3 diff = camPos - lookAt;
  Vec3 camDir = Vec3::normalize(Vec3::negate(diff));
  Vec3 camRight = Vec3::cross(Vec3::up, camDir).makeNormalize();
  Vec3 camDown = Vec3::cross(camRight, camDir);

  Camera cam{camPos, camDir, camRight, camDown};
  Vec3 lightPos{-7, 10, -10};
  Light sceneLight{lightPos, Color::white};

  // scene object
  Sphere sceneSphere{Vec3::zero, 1, Color::green};
  Plane scenePlane{Vec3::up, -1, Color::purple};

  std::vector<Object *> sceneObjects;
  sceneObjects.emplace_back(&sceneSphere);
  sceneObjects.emplace_back(&scenePlane);

  float xAmount, yAmount;

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      unsigned int pixelPosition = width * x + y;

      if (width > height) {
        xAmount = ((x + 0.5) / width) * aspectRatio -
                  ((width / height) / (float)height) / 2;
        yAmount = ((height - y) + 0.5) / height;
      } else if (height > width) {
        xAmount = (x + 0.5) / width;
        yAmount = (((height - y) + 0.5) / height) / aspectRatio -
                  (((float)(height - width) / (float)width) / 2);
      } else {
        xAmount = (x + 0.5) / width;
        yAmount = ((height - y) + 0.5) / height;
      }

      Vec3 camRayOrigin = cam.position;
      Vec3 camRayDirection =
          (camDir + (camRight * (xAmount - 0.5) + (camDown * (yAmount - 0.5))))
              .makeNormalize();
      Ray camRay{camRayOrigin, camRayDirection};
      std::vector<float> intersections;

      for (auto *object : sceneObjects) {
        intersections.emplace_back(object->findIntersection(camRay));
      }

      int winningIndex = winningObjectIndex(intersections);
      printf("%d", winningIndex);

    //   if ((x > 200 && x < 440) && (y > 200 && y < 480)) {
    //     frameBuffer[pixelPosition] = 0xff17de0a;
    //   } else {
    //     frameBuffer[pixelPosition] = 0xff000000;
    //   }
    }
  }
}

#ifdef __cplusplus
}
#endif

int main() {
    render();
}