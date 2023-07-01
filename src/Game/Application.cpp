#include "Application.hpp"
#include "../RenderEngine/Window.hpp"
#include "../RenderEngine/ShaderProgram.hpp"
#include "../RenderEngine/VertexBuffer.hpp"
#include "../RenderEngine/VertexBufferLayout.hpp"
#include "../RenderEngine/IndexBuffer.hpp"
#include "../RenderEngine/VertexArray.hpp"
#include "../RenderEngine/Texture2D.hpp"
#include "../RenderEngine/Renderer_OpenGL.hpp"
#include "../Resources/ResourceManager.hpp"
#include "../Event/Event.hpp"

#include <iostream>
#include <glad/glad.h>

namespace Game {

    GLfloat positions_texture[] = {
      -0.5f, -0.5f, 0.0f,   0.0f,  0.0f,
       0.5f, -0.5f, 0.0f,   1.0f,  0.0f,
      -0.5f,  0.5f, 0.0f,   0.0f,  1.0f,
       0.5f,  0.5f, 0.0f,   1.0f,  1.0f
    };

    GLuint indices[] = {
    0, 1, 2, 3, 2, 1
    };

    std::shared_ptr<RenderEngine::ShaderProgram> p_shader_program;
    std::shared_ptr<RenderEngine::Texture2D> p_texture;
    std::unique_ptr<RenderEngine::VertexBuffer> p_positions_colors_vbo;
    std::unique_ptr<RenderEngine::IndexBuffer> p_index_buffer;
    std::unique_ptr<RenderEngine::VertexArray> p_vao;
    GLuint vao;

    Application::Application() {
    }
    Application::~Application() {
    }

    int Application::start(unsigned int window_width, unsigned int window_height, const char* title, char** argv) {
        ResourceManager::setExecutablePath(argv[0]);
        m_pWindow = std::make_unique<RenderEngine::Window>(title, window_width, window_height);

        m_event_dispatcher.add_event_listener<EventWindowResize>(
            [](EventWindowResize& event)
            {
                std::cout << "Resized: " << event.width << "x" << event.height << std::endl;
            });

        m_event_dispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                std::cout << "WindowClose\n";
                m_bCloseWindow = true;
            });

        m_pWindow->set_event_callback(
            [&](BaseEvent& event)
            {
                m_event_dispatcher.dispatch(event);
            }
        );

        p_shader_program = ResourceManager::loadShader("default", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        p_texture = ResourceManager::loadTexture("default", "res/textures/default.png");
        if (!p_shader_program->isCompiled())
        {
            return false;
        };

        RenderEngine::BufferLayout buffer_layout_1vec3
        {
            RenderEngine::ShaderDataType::Float3
        };


        RenderEngine::BufferLayout buffer_layout_vec3_vec2
        {
            RenderEngine::ShaderDataType::Float3,
            RenderEngine::ShaderDataType::Float2
        };

        p_vao = std::make_unique<RenderEngine::VertexArray>();
        p_positions_colors_vbo = std::make_unique<RenderEngine::VertexBuffer>(positions_texture, sizeof(positions_texture), buffer_layout_vec3_vec2);
        p_index_buffer = std::make_unique<RenderEngine::IndexBuffer>(indices, sizeof(indices) / sizeof(GLuint));

        p_vao->add_vertex_buffer(*p_positions_colors_vbo);
        p_vao->set_index_buffer(*p_index_buffer);

        while (!m_bCloseWindow)
        {
            RenderEngine::Renderer_OpenGL::clear();

            p_shader_program->bind();
            p_texture->bind();

            RenderEngine::Renderer_OpenGL::draw(*p_vao);

            m_pWindow->on_update();
            on_update();
        }
        m_pWindow = nullptr;

        return 0;
    }
}