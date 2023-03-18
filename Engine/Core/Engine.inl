#include "Engine.h"

bool Engine::init(const InitInfo &init_info)
{
    Window::init();

    window.create({init_info.width, init_info.height}, init_info.title);
    window.makeCurrent();

    input.init(window);

    Renderer::init();
    Renderer::enableDebug();
    Renderer::setViewport(window.getSize());
    Renderer::clearColor(init_info.clear_color);
    Renderer::enableDepthTest();

    Node &camera_node = scene.addNode("camera");
    Camera &camera = camera_node.addComponent<Camera>();
    camera.perspective(glm::radians(45.0f), window.getAspect(), 0.01f, 100.0f);
    scene.camera = &camera;
    // scene.root.createEntity();

    return true;
}

bool Engine::cleanup()
{
    scene.clear();
    gpu.cleanup();
    window.destroy();
    Window::cleanup();

    return true;
}