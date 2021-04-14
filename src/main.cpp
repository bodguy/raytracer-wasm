#include "Camera.h"
#include "Light.h"
#include "Plane.h"
#include "Ray.h"
#include "Sphere.h"
#include <algorithm>
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

const unsigned int width = 640;
const unsigned int height = 480;
constexpr float aspectRatio = (float)width / (float)height;
const unsigned int component = 4;
uint8_t *frameBuffer = new uint8_t[width * height * component];

int winningObjectIndex(const std::vector<float> &intersections) {
  if (intersections.empty()) {
    return -1;
  }

  if (intersections.size() == 1) {
    if (intersections[0] > 0) {
      return 0;
    }
    
    return -1;
  }

  // find maximum value
  float max = *std::max_element(std::begin(intersections), std::end(intersections));
  // then start from the max value find min positive value
  int indexOfMin = 0;
  if (max > 0) {
    for (int index = 0; index < intersections.size(); index++) {
      if (intersections[index] > 0 && intersections[index] <= max) {
        max = intersections[index];
        indexOfMin = index;
      }
    }

    return indexOfMin;
  }

  // all the intersections were negative
  return -1;
}

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

  int index = 0;
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
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
      Vec3 camRayDirection = (camDir + (camRight * (xAmount - 0.5) + (camDown * (yAmount - 0.5)))).makeNormalize();
      Ray camRay{camRayOrigin, camRayDirection};
      std::vector<float> intersections;

      for (auto *object : sceneObjects) {
        intersections.emplace_back(object->findIntersection(camRay));
      }

      int winningIndex = winningObjectIndex(intersections);

      if (winningIndex == -1) {
        frameBuffer[index++] = 0;
        frameBuffer[index++] = 0;
        frameBuffer[index++] = 0;
        frameBuffer[index++] = 255;
      } else {
        Color objectColor = sceneObjects[winningIndex]->color;
        frameBuffer[index++] = Color::toByte(objectColor.r);
        frameBuffer[index++] = Color::toByte(objectColor.g);
        frameBuffer[index++] = Color::toByte(objectColor.b);
        frameBuffer[index++] = Color::toByte(objectColor.a);
      }
    }
  }

  stbi_write_png("./raytracer.png", width, height, component, frameBuffer, width * component);
  delete[] frameBuffer;
}

int main() { render(); }