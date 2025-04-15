#pragma once
#include <GLFW/glfw3.h>

namespace vtt {
class Window {
  GLFWwindow *window;
  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

public:
  void initWindow();
  bool isShoudClose();
  void DestroyWindow();
  GLFWwindow *getWindow();
  void setWindow(Window window_2);
};
} // namespace vtt