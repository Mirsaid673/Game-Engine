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

void cameraMove(Camera &camera);
Input input;
int main()
{
    Window::init();

    Window window({800, 600}, "Hello, world");
    window.makeCurrent();

    input.init(window);
    GPU gpu;

    glm::vec3 clear_color(0.8, 0.78, 0.5);
    Renderer::init();
    Renderer::enableDebug();
    Renderer::setViewport(window.getSize());
    Renderer::clearColor(clear_color);
    Renderer::enableDepthTest();

    gui::init(window);

    ProgramHandle basic = gpu.createProgram("../Engine/GPU/Shaders/Shaders/basic.vert", "../Engine/GPU/Shaders/Shaders/basic.frag");

    Model m = Resource::loadModel("model.dae");

    VertexArrayHandle vao = gpu.loadMesh(m.meshes[0]);
    TextureHandle texture = gpu.createTexture(m.meshes[0].texture_path, 4);
    texture->filter(Filter::LINEAR_MIPMAP_LINEAR);

    Camera camera;
    camera.perspective(glm::radians(45.0f), window.getAspect(), 0.01f, 100.0f);
    camera.transform.origin = {0, 0, -5};

    Transform model;
    model.rotateX(glm::radians(90.0f));
    while (not window.shouldClose())
    {
        input.update();

        if (input.getKeyDown(GLFW_KEY_ESCAPE))
            break;

        if (input.getKeyDown(GLFW_KEY_R))
            model.rotate(glm::radians(0.4f), glm::vec3(1, 1, 0));

        cameraMove(camera);

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

void cameraMove(Camera &camera)
{
    if (not input.getMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        input.enableCursor();
        return;
    }
    input.disableCursor();
    
    float sensetivity = 0.005f;
    float speed = 0.05f;

    glm::vec2 offset = input.getCursorOffset();
    camera.transform.rotate(offset.y * sensetivity, glm::vec3(1, 0, 0));
    camera.transform.rotateY(offset.x * sensetivity);

    glm::vec3 tr(0);
    if (input.getKeyDown(GLFW_KEY_W))
        tr += glm::vec3(0, 0, 1);
    if (input.getKeyDown(GLFW_KEY_S))
        tr += glm::vec3(0, 0, -1);
    if (input.getKeyDown(GLFW_KEY_A))
        tr += glm::vec3(-1, 0, 0);
    if (input.getKeyDown(GLFW_KEY_D))
        tr += glm::vec3(1, 0, 0);

    if (tr != glm::vec3(0))
        camera.transform.translate(glm::normalize(tr) * speed);

}