#include "Window.h"
#include "Log.h"

Window::Window(const glm::ivec2 &size, const std::string &title)
{
    create(size, title);
}

void Window::create(const glm::ivec2 &size, const std::string &title)
{
    m_size = size;
    m_last_size = m_size;
    m_title = title;

    m_window = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    if (m_window == nullptr)
        Log::error("Could not create window");
}

void Window::destroy()
{
    glfwDestroyWindow(m_window);
}

void Window::makeCurrent()
{
    glfwMakeContextCurrent(m_window);
}

void Window::updateSize()
{
    m_last_size = m_size;
    glfwGetWindowSize(m_window, (int *)&m_size.x, (int *)&m_size.y);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void Window::init()
{
    if (!glfwInit())
        Log::critical("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
}

void Window::cleanup()
{
    glfwTerminate();
}