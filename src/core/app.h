#pragma once

#include "imguiclient.h"
#include "eventdispatcher.h"
#include "render/renderer.h"
#include "screens/screens.h"
#include "window.h"

#include <vector>

namespace raytracing
{
    class Event;

    class App : public EventSubscriber
    {
    public:
        static App* get() { return s_Instance; }
        App();

        // Life cycle
        bool init();
        void run();
        bool onEvent(const Event& event);
        
        Renderer& getRenderer() { return m_Renderer; }

    private:
        static App* s_Instance;

        EventDispatcher m_EventDispatcher;

        Window m_Window;
        ImGuiClient m_ImGuiClient;
        std::vector<Screen*> m_Screens;

        Renderer m_Renderer;

        const char* m_Title;
        int32_t m_Width;
        int32_t m_Height;

        bool b_ShouldClose;
    };
}