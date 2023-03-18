#include "Application.h"

void Application::update()
{
    scene.camera->transform.origin =  {0, 0, -5};
}

void Application::init()
{
    Engine::init({"Hello, world", 800, 600});
}

void Application::cleanup()
{
    Engine::cleanup();
}

void Application::run()
{
    system_manager.init();
    while (not window.shouldClose())
    {
        if (input.getKeyDown(GLFW_KEY_ESCAPE))
            break;

        // update
        update();
        system_manager.update();

        // renderind
        window.updateSize();
        if (window.resized())
            scene.camera->perspective(glm::radians(45.0f), window.getAspect(), 0.01f, 100.0f);
        Renderer::setViewport(window.getSize());
        Renderer::clearBuffers();

        system_manager.draw();

        window.swapBuffers();
        
        Input::updateInput();
        input.update();
    }
    system_manager.destroy();
}