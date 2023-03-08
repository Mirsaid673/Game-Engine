#include "Renderer.h"
#include "Shaders/Program.h"
#include "GPU.h"
#include "gui.h"
#include "Window.h"
#include "Input.h"
#include "Log.h"
#include "Camera.h"
#include "Resource.h"
#include "Textures/Texture.h"

struct PosColorVertex
{
    f32 x;
    f32 y;
    f32 z;
    u32 abgr;
    f32 s;
    f32 t;
};

const PosColorVertex vertices[] =
    {
        {-1.0f, 1.0f, 1.0f, 0xff000000, 0.0f, 0.0f},  // 0----1
        {1.0f, 1.0f, 1.0f, 0xff0000ff, 1.0f, 0.0f},   // |  / |
        {-1.0f, -1.0f, 1.0f, 0xff00ff00, 0.0f, 1.0f}, // | /  |
        {1.0f, -1.0f, 1.0f, 0xff00ffff, 1.0f, 1.0f}   // 2----3
};

const u16 indices[] = {0, 1, 2, 1, 3, 2};

int main()
{
    Window::init();

    Window window({800, 600}, "Hello, world");
    window.makeCurrent();

    Input input(window);
    GPU gpu;

    glm::vec3 clear_color(0.8, 0.78, 0.5);
    Renderer::init();
    Renderer::enableDebug();
    Renderer::setViewport(window.getSize());
    Renderer::clearColor(clear_color);
    Renderer::enableDepthTest();

    gui::init(window);

    ProgramHandle basic = gpu.createProgram("../Engine/GPU/Shaders/Shaders/basic.vert", "../Engine/GPU/Shaders/Shaders/basic.frag");

    VertexBufferHandle vbo = gpu.createVertexBuffer(vertices, sizeof(vertices));
    IndexBufferHandle ibo = gpu.createIndexBuffer(indices, sizeof(indices));
    VertexArrayHandle vao = gpu.createVeretxArray();

    VertexLayout layout;
    layout.add(Attrib::Location::POSITION, DataType::FLOAT, 3)
        .add(Attrib::Location::COLOR0, DataType::UNSIGNED_BYTE, 4, true)
        .add(Attrib::Location::TEX_COORD0, DataType::FLOAT, 2);

    vao->linkIndexBuffer(ibo);
    vao->linkAttribs(vbo, layout, true);

    TextureHandle texture = gpu.createTexture("w1.jpg");
    texture->filter(Filter::LINEAR);

    Camera camera;
    camera.perspective(glm::radians(45.0f), window.getAspect(), 0.01f, 100.0f);
    camera.transform.origin = {0, 0, -5};

    Resource::loadModel("");

    Transform model;
    glm::vec3 rotation(0);
    while (not window.shouldClose())
    {
        input.update();

        if (input.getKeyDown(GLFW_KEY_ESCAPE))
            break;

        model.rotate(glm::radians(0.4f), glm::vec3(1, 1, 0));

        // renderind
        window.updateSize();
        if (window.resized())
            camera.perspective(glm::radians(45.0f), window.getAspect(), 0.01f, 100.0f);
        Renderer::setViewport(window.getSize());
        Renderer::clearColor(clear_color);
        Renderer::clearBuffers();

        basic->use();
        basic->setPVM(camera * model);
        texture->use();
        Renderer::drawVertexArray(vao);

        gui::newFrame();

        ImGui::Begin("some window");
        ImGui::ColorPicker3("color", &clear_color.x, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoBorder);
        ImGui::End();

        gui::endFrame();

        window.swapBuffers();
        Input::updateInput();
    }
    gui::cleanup();
    window.destroy();
    Window::cleanup();
}