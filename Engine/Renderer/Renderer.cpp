#include "Renderer.h"

#include "GLenums.h"
#include "Log.h"

#include <stack>

void glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

namespace Renderer
{
	void enableDebug()
	{
		GLint flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
		}
	}

	void init()
	{
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
			Log::critical("Failed to initialize GLEW");
	}

	void clearColor(const glm::vec3 &color)
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
	}

	void clearColor(u32 color)
	{
		glm::vec3 norm_color(float((color >> 24) & 0xFF) / float(0xFF),
							 float((color >> 16) & 0xFF) / float(0xFF),
							 float((color >> 8) & 0xFF) / float(0xFF));
		clearColor(norm_color);
	}

	GLenum clear_buffers = GL_COLOR_BUFFER_BIT;
	void clearBuffers()
	{
		glClear(clear_buffers);
	}

	void enableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
		clear_buffers |= GL_DEPTH_BUFFER_BIT;
	}

	glm::uvec2 viewport_size(0);
	void setViewport(const glm::uvec2 &size)
	{
		viewport_size = size;
		glViewport(0, 0, size.x, size.y);
	}

	void setViewport(const glm::uvec2 &origin, const glm::uvec2 &size)
	{
		viewport_size = size;
		glViewport(origin.x, origin.y, size.x, size.y);
	}

	void drawVertexArray(VertexArrayHandle vao)
	{
		vao->bind();
		glDrawElements(GL::translate(vao->getPrimitive()), vao->getIndexCount(), GL::translate(vao->getIndexDataType()), 0);
		vao->unbind();
	}

	std::stack<FramebufferHandle> fbo_stack;
	void pushFrambuffer(FramebufferHandle framebuffer)
	{
		fbo_stack.push(framebuffer);
		framebuffer->bind();
		setViewport(framebuffer->getSize());
	}

	void popFramebuffer()
	{
		fbo_stack.pop();

		if (fbo_stack.empty())
		{
			Framebuffer::bindMain();
			return;
		}

		FramebufferHandle framebuffer = fbo_stack.top();
		framebuffer->bind();
		setViewport(framebuffer->getSize());
	}
}

#include <iostream>
void glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
		return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:
		std::cout << "Source: API";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		std::cout << "Source: Window System";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		std::cout << "Source: Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		std::cout << "Source: Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		std::cout << "Source: Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		std::cout << "Source: Other";
		break;
	}
	std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
		std::cout << "Type: Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		std::cout << "Type: Deprecated Behaviour";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		std::cout << "Type: Undefined Behaviour";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		std::cout << "Type: Portability";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		std::cout << "Type: Performance";
		break;
	case GL_DEBUG_TYPE_MARKER:
		std::cout << "Type: Marker";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		std::cout << "Type: Push Group";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		std::cout << "Type: Pop Group";
		break;
	case GL_DEBUG_TYPE_OTHER:
		std::cout << "Type: Other";
		break;
	}
	std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "Severity: high";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "Severity: medium";
		break;
	case GL_DEBUG_SEVERITY_LOW:
		std::cout << "Severity: low";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		std::cout << "Severity: notification";
		break;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}