#include "window.hpp"

namespace vtt {
void Window::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  window = glfwCreateWindow(WIDTH, HEIGHT, "VulkanTutorial", nullptr, nullptr);
}
bool Window::isShoudClose() { return !glfwWindowShouldClose(window); }
void Window::DestroyWindow() { glfwDestroyWindow(window); }
GLFWwindow *Window::getWindow() { return window; }
} // namespace vtt