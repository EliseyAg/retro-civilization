#include "Renderer_OpenGL.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "VertexArray.hpp"


namespace RenderEngine {

    bool Renderer_OpenGL::init(GLFWwindow* pWindow)
    {
        glfwMakeContextCurrent(pWindow);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }

        std::cout << "OpenGL context initialized:" << std::endl;
        std::cout << "  Vendor: " << get_vendor_str() << std::endl;
        //std::cout << "  Renderer: " << get_renderer_str() << std::endl;
        std::cout << "  Version: " << get_version_str() << std::endl;

        return true;
    }

    void Renderer_OpenGL::draw(const VertexArray& vertex_array)
    {
        vertex_array.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertex_array.get_indices_count()), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer_OpenGL::set_clear_color(const float r, const float g, const float b, const float a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer_OpenGL::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer_OpenGL::set_viewport(const unsigned int width, const unsigned int height, const unsigned int left_offset, const unsigned int bottom_offset)
    {
        glViewport(left_offset, bottom_offset, width, height);
    }

    const char* Renderer_OpenGL::get_vendor_str()
    {
        return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
    }

    //const char* Renderer_OpenGL::get_renderer_str()
    //{
    //    return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
    //}

    const char* Renderer_OpenGL::get_version_str()
    {
        return reinterpret_cast<const char*>(glGetString(GL_VERSION));
    }

    void Renderer_OpenGL::enable_depth_testing()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer_OpenGL::disable_depth_testing()
    {
        glDisable(GL_DEPTH_TEST);
    }
}