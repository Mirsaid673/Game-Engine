#pragma once

#include "Window.h"

class Input
{
public:
    enum State
    {
        RELEASE = GLFW_RELEASE,
        PRESS = GLFW_PRESS,
    };

private:
    int last_keys_state[348];
    int last_mouse_butons_state[8];
    GLFWwindow *window;
    glm::ivec2 cursor_last_pos;
    glm::ivec2 cursor_pos;
    int muouse_scroll;

    static void mouseScrollCallback(GLFWwindow *wnd, double, double y_offset);
    static void cursorPosCallback(GLFWwindow *wnd, double x, double y);

public:
    static void updateInput();

    Input() = default;
    Input(const Window &_window) { init(_window); }

    void init(const Window &_window);
    void update();

    int getKey(int key) { return glfwGetKey(window, key); }
    bool getKeyDown(int key) { return getKey(key) == PRESS; }
    bool getKeyUp(int key) { return getKey(key) == RELEASE; }
    bool getKeyPress(int key) { return getKey(key) == PRESS && last_keys_state[key] == RELEASE; }
    bool getKeyRelease(int key) { return getKey(key) == RELEASE && last_keys_state[key] == PRESS; }

    int getMouseButton(int mouse_button) { return glfwGetMouseButton(window, mouse_button); }
    bool getMouseButtonDown(int mouse_button) { return getMouseButton(mouse_button) == PRESS; }
    bool getMouseButtonUp(int mouse_button) { return getMouseButton(mouse_button) == RELEASE; }
    bool getMouseButtonPress(int mouse_button) { return getMouseButton(mouse_button) == PRESS && last_mouse_butons_state[mouse_button] == RELEASE; }
    bool getMouseButtonRelease(int mouse_button) { return getMouseButton(mouse_button) == RELEASE && last_mouse_butons_state[mouse_button] == PRESS; }

    glm::ivec2 getCursorPos() { return cursor_pos; }
    glm::ivec2 getCursorLastPos() { return cursor_last_pos; }
    glm::ivec2 getCursorOffset() { return cursor_pos - cursor_last_pos; }
    int getMouseScroll() { return muouse_scroll; }

    void disableCursor() const
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    void enableCursor() const
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void setCursorPos(const glm::ivec2& pos)
    {
        cursor_last_pos = cursor_pos;
        cursor_pos = pos;
        glfwSetCursorPos(window, pos.x, pos.y);
    }
};