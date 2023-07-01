#pragma once

#include "../Event/Event.hpp"

#include <memory>

namespace RenderEngine {
    class Window;
}

namespace Game {

    class Application
    {
    public:
        Application();
        virtual ~Application();
        Application(const Application&) = delete;
        Application(Application&&) = delete;
        Application& operator=(const Application&) = delete;
        Application& operator=(Application&&) = delete;
        virtual int start(unsigned int window_width, unsigned int window_height, const char* title, char** argv);

        virtual void on_update() {};

    private:
        std::unique_ptr<RenderEngine::Window> m_pWindow;

        EventDispatcher m_event_dispatcher;
        bool m_bCloseWindow = false;

    };
}