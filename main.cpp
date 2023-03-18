#include "Application.h"
#include "Scene.h"
#include "Systems/RenderSystem.h"
#include "Shaders/Program.h"
#include "Resource.h"
#include "Textures/Texture.h"
#include "Editor.h"

struct PosColorVertex
{
    f32 x;
    f32 y;
    f32 s;
    f32 t;
};

const PosColorVertex vertices[] =
    {
        {-1.0f, 1.0f, 0.0f, 1.0f},  // 0----1
        {1.0f, 1.0f, 1.0f, 1.0f},   // |  / |
        {-1.0f, -1.0f, 0.0f, 0.0f}, // | /  |
        {1.0f, -1.0f, 1.0f, 0.0f}   // 2----3
};

const u16 indices[] = {0, 1, 2, 1, 3, 2};

void cameraMove(Camera &camera);
void drawIerarchy(Node &root);
float getAspect(const glm::uvec2 &sz)
{
    return (float)sz.x / (float)sz.y;
}

int main()
{
    Engine::init({"Hello, world", 1200, 800});

    Editor::init();

    Camera camera;
    camera.perspective(glm::radians(45.0f), window.getAspect(), 0.01f, 100.0f);
    camera.transform.origin = {0, 0, -5};
    scene.camera = &camera;

    ProgramHandle basic = gpu.createProgram("../Engine/GPU/Shaders/Shaders/basic.vert", "../Engine/GPU/Shaders/Shaders/basic.frag");
    ProgramHandle pproc = gpu.createProgram("../Engine/GPU/Shaders/Shaders/pproc.vert", "../Engine/GPU/Shaders/Shaders/pproc.frag");

    Model m = Resource::loadModel("model.dae");

    TextureHandle texture = gpu.createTexture(m.meshes[0].texture_path, 4);
    texture->filter(Filter::LINEAR_MIPMAP_LINEAR);

    VertexArrayHandle screen_q = gpu.createVeretxArray();
    screen_q->linkIndexBuffer(gpu.createIndexBuffer(indices, sizeof(indices)));
    screen_q->linkAttribs(
        gpu.createVertexBuffer(vertices, sizeof(vertices)),
        {{Attrib::Location::POSITION, 2}, {Attrib::Location::TEX_COORD0, 2}});

    Node &root = scene.addNode("root");
    root.addComponent<Mesh>(m.meshes[0]);
    root.addComponent<Drawable>();
    root.addComponent<Transform>();
    auto &m_c = root.addComponent<Material>();
    m_c.diffuse_texture = texture;
    m_c.program = basic;

    RenderSystem::submit();
    system_manager.init();

    FramebufferHandle fbo = gpu.createFramebuffer(window.getWidth(), window.getHeight());

    while (not window.shouldClose())
    {
        if (input.getKeyPress(GLFW_KEY_ESCAPE))
            break;

        cameraMove(camera);

        // renderind
        window.updateSize();
        if (scene.resized)
        {
            camera.perspective(glm::radians(45.0f), getAspect(scene.viewport_size), 0.01f, 100.0f);
            fbo->resize(window.getSize());
        }
        Renderer::pushFrambuffer(fbo);
        Renderer::clearBuffers();

        system_manager.draw();

        Renderer::popFramebuffer();
        Renderer::setViewport(window.getSize());
        Renderer::clearBuffers();

        pproc->use();
        pproc->setScalar("tex", 0);
        fbo->getTexture()->use();
        Renderer::drawVertexArray(screen_q);

        Editor::draw(fbo);

        window.swapBuffers();
        input.update();
        Input::updateInput();
    }
    Editor::cleanup();
    Engine::cleanup();

    return 0;
}

glm::ivec2 remember_pos(0);
void cameraMove(Camera &camera)
{
    if (!Editor::sceneHovered())
        return;

    if (not input.getMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
    {
        input.enableCursor();
        return;
    }
    if (input.getMouseButtonPress(GLFW_MOUSE_BUTTON_RIGHT))
        remember_pos = input.getCursorPos();

    glm::vec2 offset = input.getCursorOffset();

    input.disableCursor();
    input.setCursorPos(remember_pos);

    float sensetivity = 0.005f;
    float speed = 0.05f;

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