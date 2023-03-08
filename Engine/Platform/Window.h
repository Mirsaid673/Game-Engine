#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include "Core.h"

class Window
{
private:
    GLFWwindow *m_window;
    std::string m_title;
    glm::ivec2 m_last_size;
    glm::ivec2 m_size;

public:
    Window(const Window &other) = delete;
    Window &operator=(const Window &other) = delete;

    Window() = default;
    Window(const glm::ivec2 &size, const std::string &title);

    void create(const glm::ivec2 &size, const std::string &title);
    void destroy();

    void makeCurrent();
    void swapBuffers();
    void updateSize();
    bool shouldClose();
    bool resized() const { return m_last_size != m_size; }

    glm::ivec2 getSize() const { return m_size; }
    std::string getTitle() const { return m_title; }
    i32 getWidth() const { return m_size.x; }
    i32 getHeight() const { return m_size.y; }
    f32 getAspect() { return f32(getWidth()) / f32(getHeight()); }

    operator GLFWwindow *() { return m_window; }
    operator GLFWwindow *() const { return m_window; }

public:
    static void init();
    static void cleanup();
};